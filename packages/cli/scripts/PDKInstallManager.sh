#!/bin/bash

SDK_URL="http://sdk.insyber.com/Releases_Syberos_Pdk/"
Target_URL="http://sdk.insyber.com/Releases_Syberos_Pdk/"
declare -a target_package_array
declare -A arch_branch_array

SDKDIR="sdk/sdk-root"
DOWNLOAD_OUTPUT="/tmp"

function Usage()
{
    local command_name=$(basename $0)

    echo\
    "
    ${command_name} -- script to automatically install platform sdk and sb2 target
    default install target is main_dev,can change it.  
    ========pdk is platform sdk====================

    options:
    --help                  show help info
    --arch                  sb2 arch target(armv7tnhl or i686)
    --branch                target branch name, default main_dev. (main_dev or xuanwu,miit_cert,product_lily,ginkgo_millet,product_rockchip)
    --sdk-package           path of sdk installation pacakge,
                            support local package and remote package (http, ftp)
    --target-package        path of sb2 target installation package,
                            support local package and remote package (http, ftp)
    --sdk-install-path      path to install sdk(若用户没有定义，默认安装路径为~/Syberos-Pdk)
    --target-install-path   path to install sb2 target
    --sdk-alias-name        name to write alias command in ~/.bashrc
    --only-install-target   only install sb2 target
    --sudo-password         sudo password
    --silent                slient mode

    参数:
    --help                 显示帮助信息
　　--arch                 target的架构平台，可选参数(armv7tnhl or i686)
    --branch               target的分支名，可选参数(main_dev or xuanwu,miit_cert,product_lily,ginkgo_millet)
    --sdk-package          sdk的安装包路径，可选择本地路径的安装包，也支持http和ftp的安装包
　　--target-package       target的安装包路径，可选择本地路径的安装包，也支持http和ftp的安装包
    --sdk-install-path     sdk的安装路径(若用户没有定义，默认安装路径为~/Syberos-Pdk)
　　--target-install-path　target的安装路径
    --sdk-alias-name       定义别名，写入~/.bashrc
    --only-install-target　只安装target (主要用于从服务器上下包时，该参数可用)
　　--sudo-password        sudo时的密码
    --silent               静默模式
    "
}
function DownloadFile()
{
    echo "Downloading..... please wait...."
    local fromurl=$1
    local user=$2
    local password=$3
    
    local excmd="wget --timeout=12 --tries=3 --no-check-certificate --timestamping -P /tmp"
    [ "x${user}" != "x" ] && excmd="${excmd} --user=${user}"
    [ "x${password}" != "x" ] && excmd="${excmd} --password=${password}"
    excmd="${excmd} ${fromurl}"
    eval ${excmd}
    
    return $?
}

function ReadPassword()
{
    if [ "x" == "x${sudo_password}" ]; then
        read -s -p "请输入当前用户名的密码:" sudo_password
    fi
}

function sudoExec()
{
    expect <<_EOF_
    log_user 1
    set timeout 30000
    spawn sudo $@
    expect {
        "(yes/no)?" {send "yes\r"; exp_continue}
        "password" {send -- "${sudo_password}\r"; exp_continue}
	"密码" {send -- "${sudo_password}\r"; exp_continue}
        eof {}
    }
    catch wait result 
    exit [lindex \$result 3]
_EOF_
}

function SudoExec()
{
 
  if [ "x" == "x${sudo_password}" ]; then
          echo "password is null"
          exit 1
  else
        echo $sudo_password|sudo -S $@
  fi

}

function read_config_file()
{
   while read line
   do
        TITLE_NAME=${line%%=*}
        if [ "$TITLE_NAME"x == "sdk-version"x ];then
           sdk_version=${line##*=}
           break
        fi
        if [ "$TITLE_NAME"x == "target-version"x ];then
           target_version=${line##*=}
           break
        fi
   done < $1
   return 0
}
function ParseVersion()
{
  local file=$1
  read_config_file $file
   
 
}
function PreInstallSDK()
{
    local ret

    if [[ ${sdk_package} =~ (^http://|^ftp://) ]]; then

        if [ ${sdk_package_flag} -ne 1 ];then
	   DownloadFile ${SDK_URL%/}/sdk-${sdk_branch}/sdk-version-${sdk_branch}.txt
           ParseVersion $DOWNLOAD_OUTPUT/sdk-version-${sdk_branch}.txt
           sdk_package=${SDK_URL%/}/sdk-${sdk_branch}/syberos_sdk-${sdk_branch}-build${sdk_version}.tar.bz2
        fi
        DownloadFile ${sdk_package}
        ret=$?
        if [ $ret -ne 0 ]; then
            echo "download SDK package ${sdk_package} fail"
            exit 1
        fi
        echo "download SDK package ${sdk_package} ok"
	sdk_package=$DOWNLOAD_OUTPUT/$(basename ${sdk_package})
    else
        if [ ! -f ${sdk_package} ]; then
            echo "SDK package ${sdk_package} not exists"
            exit 1
        fi
    fi
    

    return 0
}

function SelectAnotherPath()
{
    local oldpath=$1
    local overwrite=
    local newvalue=
    local message=$2
 
    sdk_install_path=$oldpath
		if [ ! -d ${sdk_install_path} ]; then
			SudoExec mkdir -p ${sdk_install_path}
			if [ $? -ne 0 ]; then
				echo "mkdir ${sdk_install_path} fail"
				exit 1
			fi
		else
			SudoExec rm -rf ${oldpath%/}/*
			if [ $? -ne 0 ]; then
				echo "rm  ${sdk_install_path}/* fail,Device is busy!!!"
				exit 1
			fi
		fi
}

function silentModeCreatInstallSDKPath()
{
     local InstallPath=$1
        if [ -d $InstallPath ]; then
	   SudoExec rm  ${InstallPath%/}/* -rf
	fi
	SudoExec mkdir -p $InstallPath
}

function InstallSDK()
{
    if [ $silent_flag -eq 1 ]; then
	silentModeCreatInstallSDKPath $sdk_install_path
    else
	if [ ! -d ${sdk_install_path} ]; then
		SelectAnotherPath ${sdk_install_path} "是否安装在默认路径下${sdk_install_path}"
	else
		SelectAnotherPath ${sdk_install_path} "${sdk_install_path}已经存在，是否覆盖"
	fi
    fi
    
    if [ -f ${HOME}/.config/qtversions.conf ]; then
	rm ${HOME}/.config/qtversions.conf
    fi
    
    if [ -d ${HOME}/.scratchbox2 ]; then
        SudoExec rm -rf ${HOME}/.scratchbox2
    fi
	
    if [ ${target_install_path_flag} -ne 1 ]; then
	  target_install_path="${sdk_install_path%/}/targets"
    fi

    echo "being Install ${sdk_package}......"
    SudoExec tar --numeric-owner -p -xjf ${sdk_package} -C ${sdk_install_path}
    [ $? -ne 0 ] && echo "extract ${sdk_package} fail" && exit 1

    SudoExec chown -R $USER ${sdk_install_path%/}/
    my_uid=$(echo $(id -u))
    sed -i "/^[^:]*:[^:]*:${my_uid}/d" ${sdk_install_path%/}/$SDKDIR/etc/passwd
    SudoExec chown -R root:root ${sdk_install_path%/}/$SDKDIR
    SudoExec chmod u+s ${sdk_install_path%/}/$SDKDIR/usr/bin/sudo

    if [ -f ${sdk_install_path%/}/sdk/script/kchroot ]; then
        SudoExec chown -R root:root ${sdk_install_path%/}/sdk/script/kchroot
	SudoExec chmod u+s ${sdk_install_path%/}/sdk/script/kchroot
    fi
    
    if [ -f ${sdk_install_path%/}/sdk/script/uninstall_bin ]; then
        SudoExec chown -R root:root ${sdk_install_path%/}/sdk/script/uninstall_bin
	SudoExec chmod u+s ${sdk_install_path%/}/sdk/script/uninstall_bin
        if [ -f ${sdk_install_path%/}/sdk/uninstall ]; then
             SudoExec rm -f ${sdk_install_path%/}/sdk/uninstall
	fi
        SudoExec ln -s ${sdk_install_path%/}/sdk/script/uninstall_bin ${sdk_install_path%/}/sdk/uninstall
    fi

    [ ! -f ${sdk_install_path%/}/$SDKDIR/syberos-sdk-chroot ] && \
        echo "${sdk_install_path%/}/$SDKDIR/syberos-sdk-chroot not exists, please ensure that you have install correct Platform SDK package." && \
        exit 1

    grep "alias ${sdk_alias_name}=" ${HOME}/.bashrc 1>/dev/null 2>&1 && \
        sed -i "/alias ${sdk_alias_name}=/d" ${HOME}/.bashrc;

    grep "alias ${sdk_alias_name}=" ${HOME}/.bashrc 1>/dev/null 2>&1 || \
        echo "alias ${sdk_alias_name}=$(readlink -f ${sdk_install_path%/}/$SDKDIR/syberos-sdk-chroot)" >> "${HOME}/.bashrc"; source ${HOME}/.bashrc;


    grep "sdk-install-path" ${HOME}/.config/qtversions.conf 1>/dev/null 2>&1 && \
        sed -i "/^sdk-install-path/d" ${HOME}/.config/qtversions.conf;

    grep "sdk-install-path" ${HOME}/.config/qtversions.conf 1>/dev/null 2>&1 || \
        echo "sdk-install-path=${sdk_install_path%/}" >> "${HOME}/.config/qtversions.conf";

    [ ! -f ${HOME}/.syberossdk.profile ]  && \
        echo 'PS1="SyberOS-SDK $PS1"' > ${HOME}/.syberossdk.profile;

     [ -d ${sdk_install_path%/}/sdk/qt-examples ] && \
	find ${sdk_install_path%/}/sdk/qt-examples/ -type f|xargs touch	

    return 0
}

function PreInstallTarget()
{
    local ret

    if [[ ${target_package} =~ (^http://|^ftp://) ]]; then
        
	if [ $target_package_flag -ne 1 ]; then
           DownloadFile ${Target_URL%/}/target-${arch}-${branch}/target-version-${arch}-${branch}.txt
           ParseVersion $DOWNLOAD_OUTPUT/target-version-${arch}-${branch}.txt
           target_package=${Target_URL%/}/target-${arch}-${branch}/target-${arch}-${branch}-build${target_version}.tar.bz2
        fi

#        local user_target_package=$(basename ${target_package})
#        target_name="${user_target_package%%-build*}"

        DownloadFile ${target_package}
        ret=$?
        if [ $ret -ne 0 ]; then
            echo "download SB2 target package ${target_package} fail"
            exit 1
        fi
        echo "download SB2 target package ${target_package} ok"
	target_package=$DOWNLOAD_OUTPUT/$(basename ${target_package})
    else
        if [ ! -f ${target_package} ]; then
            echo "SB2 target package ${target_package} not exists"
            exit 1
        fi
    fi
    

    return 0
}

function SelectAnotherPathTarget()
{
    
    local oldpath=$1
    local overwrite=
    local newvalue=
    echo 
    while true
    do
        read -p "${target_install_path%/}/${target_name} 已经存在, 是否覆盖它[y/n]?" overwrite
        if [ ${overwrite} == "n" ]; then
            read -p "请输入新的绝对路径:" newvalue
           # if [ -d ${target_install_path%/}/${target_name} ]; then
           #     target_name=${newvalue}
           #     continue
	    if [ -d ${newvalue} ]; then
                oldpath=$newvalue
                continue

            else
                target_install_path=$oldpath
             #   SudoExec mkdir -p ${target_install_path%/}/${target_name}
                SudoExec mkdir -p ${target_install_path}
                break
            fi
        else
            SudoExec rm -rf ${target_install_path%/}/${target_name}/*
            break
        fi
    done
}
function silentModeCreatInstallTargetPath()
{
	local installPath=$1
	if [ -d $installPath/${target_name} ];then
	   SudoExec rm  $installPath/${target_name} -rf
	fi
	SudoExec  mkdir -p $installPath
}

function InstallTarget()
{
     if [ $silent_flag -eq 1 ]; then
            silentModeCreatInstallTargetPath ${target_install_path} 
     else
	    if [ ! -d ${target_install_path%/}/${target_name} ]; then
	       # SudoExec mkdir -p ${target_install_path%/}/${target_name}
		SudoExec mkdir -p ${target_install_path}
		if [ $? -ne 0 ]; then
		    echo "mkdir ${target_install_path} fail"
		    exit 1
		fi
	    else
		SelectAnotherPathTarget ${target_install_path}
	    fi
     fi

    echo "being Install ${target_package}....."
    SudoExec tar --numeric-owner -p -xjf ${target_package} -C ${target_install_path%/}/
    [ $? -ne 0 ] && echo "extract ${target_package} fail" && exit 1
    SudoExec chown -R $USER ${target_install_path%/}/${target_name}/*
    my_uid=$(echo $(id -u))
    sed -i "/^[^:]*:[^:]*:${my_uid}/d" ${target_install_path%/}/${target_name}/etc/passwd
    grep :$(id -u): /etc/passwd >> ${target_install_path%/}/${target_name}/etc/passwd
    grep :$(id -g): /etc/group >> ${target_install_path%/}/${target_name}/etc/group
   
    sed -i "s#\$SDK_INSTALL_PATH#${sdk_install_path%/}#g" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake.query

    grep "${target_name}" ${HOME}/.config/qtversions.conf 1>/dev/null 2>&1 && \
        sed -i "/^${target_name}/d" ${HOME}/.config/qtversions.conf;

    grep "${target_name}" ${HOME}/.config/qtversions.conf 1>/dev/null 2>&1 || \
        echo "${target_name}=${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake" >> "${HOME}/.config/qtversions.conf";
    if [ "x$arch" == "xarmv7tnhl" ];then 
        SudoExec ${sdk_install_path%/}/$SDKDIR/syberos-sdk-chroot "cd /parentroot/$(readlink -f ${target_install_path%/}/${target_name}) && sb2-init -d -L \"--sysroot=/\" -C \"--sysroot=/\" -c /usr/bin/qemu-arm-dynamic -m sdk-build -n -N -t / ${target_name} /opt/cross/bin/armv7tnhl-meego-linux-gnueabi-gcc"
        #sed -i "s#\$TARGET_INSTALL_PATH#${target_install_path%/}#g" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake.query
        sed -i "/cat\ /{s#\$TARGET_INSTALL_PATH#${target_install_path%/}#g}" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake
        sed -i "s#\$TARGET_INSTALL_PATH#\/parentroot${target_install_path%/}#g" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake 
        sed -i "/cat\ /{s#\$TARGET_INSTALL_PATH#${target_install_path%/}#g}" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake.originfix
        sed -i "s#\$TARGET_INSTALL_PATH#\/parentroot${target_install_path%/}#g" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake.originfix
        sed -i "s#\$TARGET_INSTALL_PATH#${target_install_path%/}#g" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake.query
    else
        if [ ! -d ${HOME}/.scratchbox2 ]; then
		mkdir -p ${HOME}/.scratchbox2
	fi
	sed -i "s#\$TARGET_INSTALL_PATH#\/parentroot${target_install_path%/}#g" ${target_install_path%/}/${target_name}/scratchbox2/${target_name}/sybersdk-target-i686.config ${target_install_path%/}/${target_name}/exec_${target_name}
        cp -r ${target_install_path%/}/${target_name}/scratchbox2/*  $HOME/.scratchbox2/
        SudoExec mv ${target_install_path%/}/${target_name}/exec_${target_name}  ${sdk_install_path%/}/${SDKDIR}/usr/bin/
        sed -i "/cat\ /{s#\$TARGET_INSTALL_PATH#${target_install_path%/}#g}" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake
        sed -i "s#\$TARGET_INSTALL_PATH#\/parentroot\/parentroot${target_install_path%/}#g" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake 
        sed -i "/cat\ /{s#\$TARGET_INSTALL_PATH#${target_install_path%/}#g}" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake.originfix
        sed -i "s#\$TARGET_INSTALL_PATH#\/parentroot\/parentroot${target_install_path%/}#g" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake.originfix
        sed -i "s#\$TARGET_INSTALL_PATH#${target_install_path%/}#g" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake.query
        sed -i "s#^QT_COMPILE_ARGS:sb2 -t ${target_name} -R#QT_COMPILE_ARGS:exec_${target_name}#g" ${target_install_path%/}/${target_name}/usr/lib/qt5/bin/qmake.query
	SudoExec chown -R root:root ${target_install_path%/}/${target_name}
        SudoExec chmod u+s ${target_install_path%/}/${target_name}/usr/bin/sudo
    fi


    return 0
}

function ShowResultinfo()
{
    if [ ${target_package_flag} -eq 1 ] && [ ${sdk_package_flag} -ne 1 ]; then
        echo "only install target!!!"
    else
	if [ ${only_install_target} -ne 1 ]; then
		echo \
	"--------------------------------------------
	Platform SDK Infomation
	installation package: ${sdk_package}
	location: $(readlink -f ${sdk_install_path})
	alias name: ${sdk_alias_name}"
	fi
    fi

    if [ ${target_package_flag} -ne 1 ] && [ ${sdk_package_flag} -eq 1 ]; then
        echo "only install sdk!!!"
    else
	if [ ${only_install_sdk} -ne 1 ]; then
		echo \
	"--------------------------------------------
	ScratBox2 target Infomation
	installation package: ${target_package}
	location: $(readlink -f ${target_install_path%/}/${target_name})
	target name: ${target_name}"
	fi
    fi

    echo "--------------------------------------------"
    echo "Just enjoy it!"
}


function ArgParse()
{
    local index=0;
    sudo_password=""
    branch="main_dev"
    arch="armv7tnhl"
    sdk_branch="main_dev"

    sdk_install_path_flag=0
    only_install_sdk=0
    sdk_package="${SDK_URL%/}/sdk-${sdk_branch}/syberos_sdk-build1.tar.bz2"
    sdk_install_path="${HOME}/Syberos-Pdk"
    sdk_alias_name="pdk"


    target_package_flag=0
    target_name_flag=0
    only_install_target=0
    only_install_arch_flag=0
    target_install_path_flag=0
    sdk_package_flag=0
    silent_flag=0
    branch_flag=0
    target_package="${Target_URL%/}/target-${arch}-${branch}/target-${arch}-${branch}-build1.tar.bz2"
    target_package_array[0]="${Target_URL%/}/target-${arch}-${branch}/target-${arch}-${branch}-build1.tar.bz2"

    branch_array=()
    

    target_install_path="/srv/syberos/targets"
    target_name="${target_package%%.tar.bz2}"

    while [ -n "$1" ];
    do
        case "$1" in
            --help)
                Usage
                exit 0
                ;;
            --sudo-password)
                shift
                sudo_password=$1
                shift
                ;;
            --sdk-branch)
               shift
               sdk_branch=$1
               shift
	       ;;
            --branch)
                shift
                branch_array[${#branch_array[@]}]=$1
		branch_flag=1
                shift
                ;;
            --arch)
                shift
                arch=$1
                only_install_arch_flag=1
                shift
                ;;
            --only-install-sdk)
                only_install_sdk=1
                shift
                ;;
            --sdk-package)
                shift
                sdk_package=$1
	        sdk_package_flag=1
                shift
                ;;
            --sdk-install-path)
                shift
                sdk_install_path=$1
                sdk_install_path_flag=1
                shift
                ;;
            --sdk-alias-name)
                shift
                sdk_alias_name=$1
                shift
                ;;
            --only-install-target)
                only_install_target=1
                shift
                ;;
            --target-package)
                shift
                target_package_array[${#target_package_array[@]}]=$1
                target_package_flag=1
                shift
                ;;
            --target-install-path)
                shift
                target_install_path=$1
		target_install_path_flag=1
                shift
                ;;
	    --silent)
		silent_flag=1
		shift
 		;;
	    --archbranch)
		shift
		archbranch=()
		while [ -n "$1" ];
		 do
                    (echo "$1" | grep "^--") 1>/dev/null 2>&1 && break
                    n=${#archbranch[@]}
                    archbranch[n]=$1
                    shift
		    if [ $n == 1 ]; then break;
		    fi
                    ((n++))
                done
		;;
         #   --target-name)
         #       shift
         #       target_name=$1
         #       target_name_flag=1
         #       shift
         #       ;;
            *)
                echo "invalid option -- $1"
                exit 1
        esac
	local result=`expr ${#archbranch[@]} % 2`
	if [ ${#archbranch[@]} != 0 ] && [ $result == 0 ]; then
	   local array_index="${archbranch[0]}-${index}"
	   arch_branch_array[${array_index}]=${archbranch[1]}
	   ((index++))
           unset archbranch
	fi
    done
    
    if [ ${target_package_flag} -ne 1 ]; then
	    target_package_array[0]="${Target_URL%/}/target-${arch}-${branch}/target-${arch}-${branch}-build1.tar.bz2"
    fi
#    else
#        local user_package=$(basename ${target_package})
#        arch=`echo $user_package|cut -f2 -d-`
#    fi
     
    if [ ${sdk_install_path_flag} -eq 1 -a $target_install_path_flag -ne 1 ];then
         target_install_path="${sdk_install_path%/}/targets"
    fi 

#    if [ ${target_name_flag} -ne 1 ]; then
#        local user_target_package=$(basename ${target_package})
#        target_name="${user_target_package%%-build*}"
#    fi
    if [ ${only_install_target} -eq 1 -a ${sdk_install_path_flag} -eq 1 ];then
        if [ ! -d ${sdk_install_path%/}/$SDKDIR ];then
	       echo "error:${sdk_install_path%/}/$SDKDIR is not exist!!!"
               exit 1
        fi
    fi

    if [ ${target_package_flag} -eq 1 -a ${sdk_install_path_flag} -eq 1 -a ${sdk_package_flag} -ne 1 ];then
        if [ ! -d ${sdk_install_path%/}/$SDKDIR ];then
	       echo "error:${sdk_install_path%/}/$SDKDIR is not exist!!!"
               exit 1
        fi
    fi

    if [ ${only_install_sdk} -eq 1 -a ${only_install_target} -eq 1 ]; then
        echo "option --only-install-sdk and --only-install-target can't be set at the same time"
        exit 1
    fi
    if [ ${only_install_target} -eq 1 -a ${sdk_install_path_flag} -ne 1 ];then
        echo "option --sdk-install-path and --only-install-target must be set at the same time"
        exit 1
    fi
    if [ ${sdk_package_flag} -ne 1 ]; then
       if [ ${target_package_flag} -eq 1 -a ${sdk_install_path_flag} -eq 0 ]; then
          echo "option --sdk-install-path and --target-package must be set at the same time"
          exit 1
       fi

       if [ ${target_package_flag} -eq 1 -a ! -f ${sdk_install_path%/}/$SDKDIR/syberos-sdk-chroot ]; then
          echo "option --sdk-install-path ${sdk_install_path%/} error"
          exit 1
       fi
    fi

}

function exec_install_target()
{

    local ret
    if [ ${target_package_flag} -ne 1 ] && [ ${sdk_package_flag} -eq 1 ]; then
        echo "only install sdk!!!"
    else
            if [ ${only_install_sdk} -ne 1 ]; then
              for package_name in ${target_package_array[@]}
                do
                        if [ $target_package_flag -eq 1 ];then
                                if [ "x$package_name" == x$target_package ]; then
                                        continue;
                                fi
                        fi

                        target_package=$package_name
                        local user_target_package=$(basename ${target_package})
			if [ ${only_install_arch_flag} -ne 1 ];then
				arch=`echo $user_target_package|cut -f2 -d-`
			fi

			if [ $branch_flag != 0 ]; then
				target_name="target-$arch-$branch"
			else
				target_name="${user_target_package%%-build*}"
			fi
			
                        PreInstallTarget
                        echo "It will be install ${target_package}............"
                        InstallTarget
                        ret=$?
                        if [ $ret -ne 0 ]; then
                            echo "scratbox2 target install fail."
                            exit 1
                        fi
                        echo "scratbox2 target install successfully."
                done
            fi
    fi

    if [ ${sdk_package_flag} -ne 1 -a ${only_install_sdk} -ne 1 ] && [ ${only_install_arch_flag} -ne 1 -a ${target_package_flag} -ne 1 ]; then
        arch="i686"
        target_package=${Target_URL%/}/target-${arch}-${branch}/target-${arch}-${branch}-build1.tar.bz2
        local user_package=$(basename ${target_package})
	if [ ${#branch_array[@]} != 0 ]; then
		target_name="target-$arch-$branch"
	else
		target_name="${user_package%%-build*}"
	fi
        PreInstallTarget
        echo "It will be install ${target_package}............"
        InstallTarget
        ret=$?
        if [ $ret -ne 0 ]; then
            echo "scratbox2 i686 target install fail."
            exit 1
        fi
        echo "scratbox2 i686 target install successfully."
    fi

}

function print_array()
{
  for key in "${!arch_branch_array[@]}"
  do
    echo "key::$key value:: ${arch_branch_array[${key}]}"
  done
}

function main()
{
    local ret

    ArgParse "$@"
  #  print_array
    ReadPassword
#    sudo_password=$(echo -n $sudo_password |sed -e 's/\$/\\\$/g'|sed -e 's/\}/\\\}/g')
#    sudo_password=$(echo -n $sudo_password |sed -e 's/{/\\\{/g')
    echo 
    echo "Verify Password......"
    if [ -f /tmp/test_passwd ]; then
      SudoExec rm -f /tmp/test_passwd
    fi

    SudoExec echo "test_passwd" > /tmp/test_passwd
    ret=$?
    if [ $ret -ne 0 ]; then
	echo "maybe you not install expect or password is not correct !!!"
        exit 1
    fi

    if [ ${target_package_flag} -eq 1 ] && [ ${sdk_package_flag} -ne 1 ]; then
        echo "only install target!!!"
    else
	    if [ ${only_install_target} -ne 1 ]; then
		PreInstallSDK
 		echo "It will be install ${sdk_package}............"
		if [ ${sdk_install_path_flag} -ne 1 ]; then
			echo "***********the default install path is $sdk_install_path****** "
		fi
		InstallSDK
		ret=$?
		if [ $ret -ne 0 ]; then
		    echo "Platform SDK install fail."
		    exit 1
		fi
		echo "Platform SDK install successfully."
	    fi
    fi
   
    if [ ${#arch_branch_array[@]} != 0 ]; then
	only_install_arch_flag=1
	branch_flag=1
	for arch_install in "${!arch_branch_array[@]}"
	do
	  arch=${arch_install%-*}
	  branch=${arch_branch_array[${arch_install}]}
	  exec_install_target
       done 
    else
    	if [ ${#branch_array[@]} != 0 ]; then
	    for branch_name in ${branch_array[@]}
	    do 
		    branch=$branch_name
		    exec_install_target
	    done
    	else
		    exec_install_target
     	fi
    fi	
    
    ShowResultinfo

    
    return 0
}

main "$@"
