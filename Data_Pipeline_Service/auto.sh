################################################
# Copyright (c) 2015, ShangHai xxxx Inc.
#
# Script Name: auto.sh
#
# Description:
#
# Created: 2015年08月20日
# Author: written by jiangzhe.
#
################################################
#! /bin/sh -

MIDDLEWARE_LIB_PATH=/usr/local/middleware/lib

SERVER_LOG_FILE=serv.log
CLIENT_LOG_FILE=cli.log

function usage()
{
    cat <<-USAGE
    usage:
         $0 install
         $0 start
         $0 stop
         $0 restart
         $0 status

	USAGE
    return 0
}

function parseArgs()                                                            
{
    while [ $# -gt 0 ];
    do
        optname=`expr "x$1" : 'x--\([^=]*\)=.*'`;
        optarg=`expr "x$1" : 'x--[^=]*=\(.*\)'`;

        #@jiangzhe 2015-08-24 for relative path
        if [[ "src" == "$optname" ]]; then
            pushd $optarg 1>/dev/null || exit 1
            optarg_abs_path=`pwd`
            popd 1>/dev/null
            eval ARG_$optname=$optarg_abs_path
        else
            eval ARG_$optname=$optarg
        fi  

        shift
    done
}


function do_install()
{
    #parseArgs $@
	echo -e "\e[1;31m\n[[ 1 ]] Install dependent library...\e[0m"
	sleep 3

    if [ ! -d ${MIDDLEWARE_LIB_PATH} ]; then
        mkdir -p ${MIDDLEWARE_LIB_PATH} || return 1
    fi
    cd dependent && sudo make

	echo -e "\e[1;31m\n[[ 2 ]] Clean data pipeline envirnoment...\e[0m"
	sleep 3

	cd ../src/ && make clean

	echo -e "\e[1;31m\n[[ 3 ]] Install data pipeline envirnoment...\e[0m"
	sleep 3

	make

    return 0
}

function do_start()
{
    #parseArgs $@
    echo -e "\e[1;31m [Start services ...]\e[0m"

	cd src/

	icegridnode --Ice.Config=config.grid >>${SERVER_LOG_FILE} 2>&1 &
	if [ $? -ne 0 ]; then
		echo "\e[1;31m icegridnode failed!\e[0m" && return 1
	fi
	sleep 2

	icegridadmin --Ice.Config=config.grid -e \
		"application add 'application.xml'" >/dev/null 2>&1
	if [ $? -ne 0 ]; then
		icegridadmin --Ice.Config=config.grid -e \
		"application update 'application.xml'"
	fi
	[ $? -ne 0 ] && echo -e "\e[1;31m icegridadmin failed!\e[0m" \
	&& return 1
	
	./client >>${CLIENT_LOG_FILE} 2>&1 &

    return 0
}

function do_stop()
{
    #parseArgs $@
	echo -e "\e[1;31m [Stop services ....]\e[0m"
	sleep 2
	
	ICENODE_PID=`ps -ef | grep [i]cegridnode |awk -F' ' '{print $2}'`
	kill -9 ${ICENODE_PID} >/dev/null 2>&1

	CLI_PID=`ps -ef | grep [c]lient$ |awk -F' ' '{print $2}'`
	for PID in ${CLI_PID}; do
		kill -9 ${PID} >/dev/null 2>&1
	done

	return 0
}

do_status()
{
	echo -e "\e[1;31m [Services status ..]\e[0m"

	echo `ps -ef | grep [i]cegridnode`
	echo `ps -ef | grep [c]lient$`
	echo -e ''

	return 0
}


## MAIN ##

#echo $@
if [ $# -gt 0 ]; then
    CMD=$1
    shift
    case "$CMD" in
    install)
        do_install $@
        exit $?;;
    start)
        do_start $@
        exit $?;;
	stop)
		do_stop $@
		exit $?;;
	restart)
		do_stop $@
		do_start $@
		exit $?;;
	status)
		do_status $@
		exit $?;;
    *)
        usage;;
    esac
else
    usage
fi
exit 255

