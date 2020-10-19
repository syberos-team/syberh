# 介绍

本项目为syberh中的插件，每一个子目录为一个插件项目

# 编译

需要：
1. python3
2. expect

在编译前，需要修改build-env中的配置

```
# 指向syberh项目中的syberos目录
SYBERH_APP=$HOME/workspace/syberh/abeir/syberh/packages/syberos
# 配置编译时使用的target
TARGET_NAME=target-armv7tnhl-os4_1_1
```

使用build.sh脚本编译插件

```shell
$ ./build.sh -b audio
```
