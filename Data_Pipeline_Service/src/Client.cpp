// **********************************************************************
//
// Copyright (c) Sari CloudBackup Group, All rights reserved.
//
// **********************************************************************

// < 1 >
#include <unistd.h>
#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
// < 2 >
#include <Ice/Ice.h>
#include <IceGrid/IceGrid.h>
#include <Datapipeline.h>
using namespace Demo;
// < 3 >
#include "iceGrid.h"
#include "parser.h"
#include "baseFunc.h"

#define GET_EVENT   "http://10.3.3.248:8080/Phoenix-Web-Service/api/Service/Queue" \
                    "/GetEvent?from=cloudfs&me=pipeline&project=cloudstorage"

#define SEND_EVENT  "http://10.3.3.248:8080/Phoenix-Web-Service/api/Service/Queue" \
                    "/SendEvent?op=OPERATION_SENDTO_QUEUE&from=pipeline&to=cloudfs&project=cloudstorage&msg="

#define ACK_EVENT   "http://10.3.3.248:8080/Phoenix-Web-Service/api/Service/Queue" \
                    "/AckEvent?project=cloudstorage&msg="

class DatapipelineClient : public Ice::Application
{
public:

    DatapipelineClient();
    virtual int run(int, char*[]);
};


// < 1 >
// **********************************************
//
//  P R O D U C E R  -  C O N S U M E R
//
// ********************************************** 

// Task capability equal [kItemRepositorySize - 1]
static const int kItemRepositorySize  = 4*4 + 1;

struct ItemRepository {
	std::string buffer[kItemRepositorySize];
	int read_position;
	int write_position;
	std::mutex mtx;
	std::condition_variable repo_not_full;
	std::condition_variable repo_not_empty;
} gItemRepository;

typedef struct ItemRepository ItemRepository;


void ProduceItem(ItemRepository *ir, std::string &jsonStr)
{
	std::unique_lock<std::mutex> lock(ir->mtx);
	// item buffer is full, just wait here.
	while(((ir->write_position + 1) % kItemRepositorySize)
			== ir->read_position) {
		std::cout << "Producer is waiting for an empty slot...\n";
		(ir->repo_not_full).wait(lock);
	}

	(ir->buffer)[ir->write_position] = jsonStr;
	(ir->write_position)++;

	if (ir->write_position == kItemRepositorySize)
		ir->write_position = 0;

	(ir->repo_not_empty).notify_all();
	lock.unlock();
}

std::string ConsumeItem(ItemRepository *ir, int argc, char *argv[])
{
	std::unique_lock<std::mutex> lock(ir->mtx);
	// item buffer is empty, just wait here.
	while(ir->write_position == ir->read_position) {
		std::cout << "Consumer is waiting for items...\n";
		(ir->repo_not_empty).wait(lock);
	}

	std::string strRequest = (ir->buffer)[ir->read_position];
	DatapipelineClient app;
	argc = ir->read_position + 1;
	argv[ir->read_position+1] = (char*)malloc(1024*4*sizeof(char));
	//if(NULL == argv[ir->read_position+1])
	//	std::cout << "malloc fail." << std::endl;
	sprintf(argv[ir->read_position+1],"%s",strRequest.c_str());
	int ret = app.main(argc, argv, "config.client");
	std::cout << "app.main return: " << ret << std::endl;

	free(argv[ir->read_position+1]);

	(ir->read_position)++;
	if (ir->read_position >= kItemRepositorySize)
		ir->read_position = 0;

	(ir->repo_not_full).notify_all();
	lock.unlock();

	return strRequest;
}

void ProducerTask()
{
	while(1) {
		MfcIceGrid iceGrid;
		sleep(5);

		// 1. get event
		std::string strUrl = GET_EVENT;
		std::string strResponse;
		iceGrid.get(strUrl, strResponse, NULL);
		//std::cout << strResponse << std::endl;
		if(!judgeValid(strResponse)) continue;

		// 2. producer
		ProduceItem(&gItemRepository, strResponse);
		std::cout << "Producer a item." << std::endl;

	}
	std::cout << "Producer thread " << std::this_thread::get_id()
		<< " is exiting..." << std::endl;
}

void ConsumerTask(int argc, char* argv[])
{
	while(1) {
		MfcIceGrid iceGrid;
		sleep(5);

		// 1. consumer
		std::string jsonMsg = ConsumeItem(&gItemRepository, argc, argv);
		std::cout << "Consumer a item." << std::endl;

		// 2. send event
		std::string sendEventUrl = SEND_EVENT;
		std::string msg = base64Decode(parseMsg(jsonMsg));
		sendEventUrl.append(base64Encode(msg));
		std::cout << sendEventUrl << std::endl;

		std::string sendEventResp;
		iceGrid.post(sendEventUrl, "", sendEventResp);
		std::cout << sendEventResp << std::endl;

		// 3. ack event
		std::string ackEventUrl = ACK_EVENT;
		ackEventUrl.append(jsonMsg);
		std::cout << ackEventUrl << std::endl;

		std::string ackEventResp;
		iceGrid.post(ackEventUrl, "", ackEventResp);
		std::cout << sendEventResp << std::endl;

	}
	std::cout << "Consumer thread " << std::this_thread::get_id()
		<< " is exiting..." << std::endl;
}

void InitItemRepository(ItemRepository *ir)
{
	ir->write_position = 0;
	ir->read_position = 0;
}


// < 2 >
// **********************************************
//
//  I C E  -  G R I D  
//
// ********************************************** 

DatapipelineClient::DatapipelineClient() :
    //
    // Since this is an interactive demo we don't want any signal
    // handling.
    //
    Ice::Application(Ice::NoSignalHandling)
{
}

int
DatapipelineClient::run(int argc, char* argv[])
{
    //if(argc > 1)
    //{
    //    std::cerr << appName() << ": too many arguments" << std::endl;
    //    std::cerr << "execute programming : " << argv[0] << std::endl;
    //    return EXIT_FAILURE;
    //}
    int i = argc;
    printf("run... [%d]\n",argc);
    printf("run... [%s]\n",argv[i]);
    std::string strRequest(argv[i]);

#if 1
	//
	// First we try to connect to the object with the `datapipeline'
	// identity. If it's not registered with the registry, we will
	// search for an object with the ::Demo::Datapipeline type.
	//
	DatapipelinePrx datapipeline;
	try
	{
		datapipeline = DatapipelinePrx::checkedCast(communicator()->stringToProxy("datapipeline"));
	}
	catch(const Ice::NotRegisteredException&)
	{
		IceGrid::QueryPrx query = IceGrid::QueryPrx::checkedCast(communicator()->stringToProxy("DemoIceGrid/Query"));
		datapipeline = DatapipelinePrx::checkedCast(query->findObjectByType("::Demo::Datapipeline"));
	}
	catch(...)
	{
		std::cerr << "unexpected exception" << std::endl;
	}
	if(!datapipeline)
	{
		std::cerr << ": couldn't find a `::Demo::Datapipeline' object." << std::endl;
	}
#endif

	try
	{
		std::string resp = datapipeline->fileTransfer(strRequest);
		std::cout << resp << std::endl;
	}
	catch(const Ice::Exception& ex)
	{
		std::cerr << ex << std::endl;
	}

	return EXIT_SUCCESS;
}


// < 3 >
// **********************************************
//
//  M A I N 
//
// ********************************************** 

int
main(int argc, char* argv[])
{
	InitItemRepository(&gItemRepository);

	// Init producers and consumers, ugly here!!!
	std::thread t1(ProducerTask);
	std::thread t2(ProducerTask);
	std::thread t3(ProducerTask);
	std::thread t4(ProducerTask);

	std::thread c1(ConsumerTask,argc,argv);
	std::thread c2(ConsumerTask,argc,argv);
	std::thread c3(ConsumerTask,argc,argv);
	std::thread c4(ConsumerTask,argc,argv);

	t1.join();    c1.join();
	t2.join();    c2.join();
	t3.join();    c3.join();
	t4.join();    c4.join();

	return 0;
}

