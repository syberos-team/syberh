#!/bin/bash

# target 中的 bin 路径
TARGET_BIN_PATH=/home/abeir/Syberos-Pdk/targets/target-armv7tnhl-os4_0/usr/lib/qt5/bin
# cdb 设备
CDB_DEVICE=acf6af5-SyberOS
# 项目根pro文件
PROJECT_PRO=/home/abeir/workspace/syberos/syberh/packages/syberos/app.pro
# 编译时使用的目录
BUILD_DIR=/home/abeir/workspace/syberos/syberh/packages/build-test1
# sop包名
SOP_NAME=com.syberos.demo-1.0.0.sop

mkdir $BUILD_DIR
cd $BUILD_DIR

#>>> build

/home/abeir/Syberos-Pdk/sdk/script/kchroot 'sb2 -t target-armv7tnhl-os4_0 -R' ${TARGET_BIN_PATH}/qmake "$PROJECT_PRO -r -spec linux-g++ CONFIG+=qml_debug"

/home/abeir/Syberos-Pdk/sdk/script/kchroot 'sb2 -t target-armv7tnhl-os4_0 -R' /usr/bin/make -j8

/home/abeir/Syberos-Pdk/sdk/script/kchroot 'sb2 -t target-armv7tnhl-os4_0 -R' buildpkg $PROJECT_PRO

#>>> cdb

#/home/abeir/Syberos-Pdk/targets/target-armv7tnhl-os4_0/usr/lib/qt5/bin/cdb devices

${TARGET_BIN_PATH}/cdb -s $CDB_DEVICE push -p $SOP_NAME /tmp

expect <<-EOF
spawn $TARGET_BIN_PATH/cdb -s $CDB_DEVICE shell
expect {
  "root@" {
    send "su install\r"
    expect "install@" {
      send "/usr/bin/ins-tool -siu /tmp/$SOP_NAME && exit\r"
      expect "root@" {send "exit\r"} 
    }
  }
}
expect eof;
EOF

${TARGET_BIN_PATH}/cdb -s $CDB_DEVICE shell
