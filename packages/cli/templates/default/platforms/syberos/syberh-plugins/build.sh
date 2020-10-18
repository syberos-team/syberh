#!/bin/bash

source ./build-env

current_dir=`pwd`

pro_path=${current_dir}/[[project]]/[[project]].pro
build_path=${current_dir}/build/[[project]]


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

project_name=''

cmd_name=`basename $0`
usage(){
    echo "Usage: $cmd_name [options]"
    echo ''
    echo '  -b    执行编译，参数为插件项目名'
    echo '  -c    执行清理，参数为插件项目名'
    echo '  -s    使用S1编译，无参'
}

get_sop_full_path(){
    sop_path=$1
    build_path=${build_path//'[[project]]'/$project_name}
    if [ "" == "$sop_path" ];then
	    sop_path=`ls --file-type ${build_path}/*.sop |awk '{print i$0}'`
    fi
    echo $sop_path
}

exec_build(){
    s1_arg=''
    if [ "$1" == "y" ];then
        s1_arg='--args DEFINES+=S1'
    fi
    pro_path=${pro_path//'[[project]]'/$project_name}
    build_path=${build_path//'[[project]]'/$project_name}
    python3 ./syberh-build.py build -b $build_path -p $pro_path -d $pdk_path -t $TARGET_NAME -n $cpu_num --args SYBERH_APP=$SYBERH_APP --args SOPID=$SOPID $s1_arg
}

exec_clear(){
    python3 ./syberh-build.py clear -b ${build_path//'[[project]]'/$project_name}
}


ACTION=''
use_s1=''
while getopts 'b:c:s' arg; 
do
    case $arg in
        b)
            ACTION="build"
            project_name="$OPTARG"
            ;;
        c)
            ACTION='clear'
            project_name="$OPTARG"
            ;;
        s)
            use_s1='y'
            ;;
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
        exec_build $use_s1
    ;;
    clear)
        exec_clear $project_name
    ;;
esac
