#!/bin/bash

source ./build-env

cpu_num=4

pdk_path=''

if [ -d "$HOME/SyberOS-Pdk" ];then
    pdk_path=$HOME/SyberOS-Pdk
elif [ -d "$HOME/Syberos-Pdk" ];then
    pdk_path=$HOME/Syberos-Pdk
else
    echo '未安装pdk'
    exit 1;
fi


cmd_name=`basename $0`
usage(){
    echo "Usage: $cmd_name [options]"
    echo ''
    echo '  -b    执行编译'
    echo '  -c    执行清理'
    echo '  -i    上传sop包'
}

get_sop_full_path(){
    sop_path=$1
    if [ "" == "$sop_path" ];then
	    sop_path=`ls --file-type ${BUILD_PATH}/*.sop |awk '{print i$0}'`
    fi
    echo $sop_path
}

exec_build(){
    python3 ./syberh-build.py build -b $BUILD_PATH -p $PRO_PATH -d $pdk_path -t $TARGET_NAME -n $cpu_num
}

exec_clear(){
    python3 ./syberh-build.py clear -b $BUILD_PATH
}

exec_install_sop(){
    sop_path=$(get_sop_full_path)
    if [ ! -f "$sop_path" ];then
        echo '未找到sop包'
        exit 1
    fi

    python3 ./syberh-build.py install -s $sop_path
}

exec_rename(){
    sop_path=$(get_sop_full_path)
    if [ ! -f "$sop_path" ];then
        echo '未找到sop包'
        exit 1
    fi
    python3 ./syberh-build.py rename -s $sop_path
}

ACTION=''
while getopts 'bci' arg; 
do
    case $arg in
        b)
            ACTION="build";;
        c)
            ACTION='clear';;
        i)
            ACTION='install';;
        ?)
            usage
            exit 0
            ;;
    esac
done


if [ ! $ACTION ];then
    usage
    exit 0
fi

case $ACTION in
    build)
        exec_build
    ;;
    clear)
        exec_clear
    ;;
    install)
        exec_install_sop
    ;;
    rename)
	    exec_rename
    ;;
esac
