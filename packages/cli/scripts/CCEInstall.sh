#!/bin/bash

ver="5_0"
target_install_folder=$1
target_install_path=${target_install_folder%/}/SyberOS-CCE/SyberOS${ver}
crosscompile_package=$2
syberos_sdk_path=$3
target_name=target-qt5.12.5-syberos-${ver}
compiler_path=${target_install_path}/compilers/aarch64-linux-gnu/bin

if [ ! -d $1/SyberOS-CCE ]
then
	mkdir -p $1/SyberOS-CCE
fi

cd $1/SyberOS-CCE
rm -rf *

if [ ! -d SyberOS${ver} ]
        mkdir -p $1/SyberOS-CCE/SyberOS${ver}
then
        cd  $1/SyberOS-CCE/SyberOS${ver}
        tar -xvJf $2
fi

cd ${target_name}

#modify qt5.12.5 folder,eg. mkspec
sed -i 's#INSTALL_CROSSCOMPILE_PATH#'${target_install_path%/}'#g' `grep -rl INSTALL_CROSSCOMPILE_PATH`
#modify sysroot/usr/bin/bulidpkg sign-binary.sh
sed -i 's#INSTALL_CROSSCOMPILE_PATH#'${target_install_path%/}'#g' ${target_install_path%/}/sysroot/usr/bin/buildpkg
sed -i 's#INSTALL_CROSSCOMPILE_PATH#'${target_install_path%/}'#g' ${target_install_path%/}/sysroot/usr/bin/sign-binary.sh
#modify sysroot/usr/lib64/cmake
cd ../sysroot/usr/lib64/cmake
sed -i 's#INSTALL_CROSSCOMPILE_PATH#'${target_install_path%/}'#g' `grep -rl INSTALL_CROSSCOMPILE_PATH`
grep "${target_name}" ${HOME}/.config/qtversions.conf 1>/dev/null 2>&1 && \
        sed -i "/^${target_name}/d" ${HOME}/.config/qtversions.conf;

grep "${target_name}" ${HOME}/.config/qtversions.conf 1>/dev/null 2>&1 || \
        echo "${target_name}=${target_install_path%/}/${target_name}/bin/qmake" >> "${HOME}/.config/qtversions.conf";
        echo "SyberOS-CCE-PATH=${target_install_folder%/}/SyberOS-CCE" >> "${HOME}/.config/qtversions.conf";
