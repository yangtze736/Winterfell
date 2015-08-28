#! /bin/bash

MIDDLEWARE_LIB_PATH=/usr/local/middleware/lib

function usage()
{
    cat <<-USAGE
    usage:
         $0 install
         $0 upgrade
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
    echo "[ 1 ] install dependent library..."
    if [ ! -d ${MIDDLEWARE_LIB_PATH} ]; then
        mkdir -p ${MIDDLEWARE_LIB_PATH} || return 1
    fi
    cd dependent && sudo make

	echo "[ 2 ] clean data pipeline envirnoment..."
	cd ../src/ && make clean

	echo "[ 3 ] install data pipeline envirnoment..."
	make

    return 0
}

function do_upgrade()
{
    #parseArgs $@
    echo "upgrade ..."
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
    upgrade)
        do_upgrade $@
        exit $?;;
    *)
        usage;;
    esac
else
    usage
fi
exit 255

