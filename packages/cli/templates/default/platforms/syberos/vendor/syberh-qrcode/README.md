# syberh-qrcode
syberh扫码模块
> S1手机如果要开发扫码功能，请克隆分支s1


## 如何把扫码模块集成到自己的项目里
1、进入自己的项目根目录下，下载代码
```javascript
git clone https://github.com/syberos-team/syberh-qrcode

// S1手机
git clone -b s1 https://github.com/syberos-team/syberh-qrcode
```

2、在自己的项目pro文件中，引入`syberh_qrcode.pri`
```C++
include (./syberh-qrcode/syberh_qrcode.pri)
```

3、在自己的项目中`App_Workspace.cpp`中, 注册需要的C++模块，根据`QRCODE`宏来判断是否导入了syberh_qrcode模块

```C++
// 引入需要的头文件
#ifdef QRCODE
#include "../syberh-qrcode/src/qrcoderegister.h"
#endif

// 注册需要的C++模块
#ifdef QRCODE
    QrcodeRegister * qrcode = new QrcodeRegister();
    qrcode->init(m_view);
#endif
```

4、在自己的项目中`syberos.pri`文件，添加`LIB_DIR`变量，`com.syberos.demo`需要替换成自己的sopid

```C++
# 引入lib库(so文件)需要添加这个变量，位于手机上/data/app-libs目录下
LIB_DIR = /data/app-libs/com.syberos.demo
```

5、由于qml组件用到了`env.dp()`方法来做适配，所以需要有env对象
> `src`文件夹下的`env`文件夹，提供了C++文件，拷贝到自己的项目，然后在`App_Workspace.cpp`中注册进去，目前是通过qt版本来判断OS是2.1还是4.1
```C++
#include <cenvironment.h>
#if (QT_VERSION < QT_VERSION_CHECK(5, 6, 0))
#include "../syberh-qrcode/src/env/senvironment.h"
#endif

// QT版本大于5.6，选择进入特定的qml页面, qml适配， 266是9860手机的dpi值
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    CEnvironment::initAppDpi(266);
#else
    SEnvironment *env = new SEnvironment;
    m_view->rootContext()->setContextProperty("env", env);
#endif
```

## syberh项目如何集成S1手机扫码模块
1、在项目根目录下的`platforms/syberos/vendor`下删除`syberh-qrcode`文件夹

2、在项目根目录下的`platforms/syberos/vendor`下,下载S1手机扫码模块
```javascript
git clone -b s1 https://github.com/syberos-team/syberh-qrcode
```