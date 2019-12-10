---
title: 应用sopconfig.xml
author: 李何佳
sidebar_label:应用sopconfig.xml
---

<div class="whats-the-point" markdown="1">

<b> <a id="whats-the-point" class="anchor" href="#whats-the-point" aria-hidden="true"><span class="octicon octicon-link"></span></a>你将会学到:</b>

- SyberOS 应用如何配置应用的名称
- SyberOS 应用如何配置启动动画
- SyberOS 应用如何配置应用图标
- SyberOS 应用的权限配置
- SyberOS 应用如何配置 service
  </div>

## sopconfig.xml 简介

- 每个 SyberOS 应用必须有一个 sopconfig.xml 文件，位于 .SOP 包的最顶层目录中。
- 用于描述该应用程序的名字、版本号、所需权限、注册的事件等。
- 该文件使用 XML 文件格式，目前的版本是 v1。
- sopconfig.xml 为系统提供应用最基本的信息，包括：应用唯一的包名称，描述应用包含哪些组件，应用所需要的权限，运行所需要的环境。

## sopconfig.xml 结构

```xml
<?xml version="1.0" encoding="utf-8"?>
<sopconfig>
    <uses-permission />
    <uses-sdk />
    <application>
        <uiapp>
        <url>
            <scheme />
        </url>
        <doctype>
            <name />
            <action />
            <mime-type />
            <extension />
        </doctype>
        <multidoc>
          <action />
        </multidoc>
        <receiver>
            <event />
        </receiver>
    </uiapp>
    <service>
        <receiver>
            <event />
        </receiver>
        <doctype>
            <name />
            <mime-type />
            <extension />
        </doctype>
    </service>
    <backup />
    </application>
</sopconfig>
```

## sopconfig

sopconfig 是 sopconfig.xml 的根元素

| 属性名              | 描述                                                                                                                                                                                                                                                                                                                                              |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| xmlns:syberos       | xmlns:syberos ： 命名空间。对于 v1 版本， 必须为“http：//schemas.syberos.com/sop/res/syberos/v1”                                                                                                                                                                                                                                                  |
| syberos:sopid       | Syber OS Package ID，包名称。可以包含大写字母、小写字母、数字、下划线、点，必须以字母开头，总长度不超过 128 字符。此名称必须唯一，为了避免冲突，开发者要使用自己拥有的域名的倒序方式。例如，元心公司发布的应用，包名称都将是以 com.syberos. 开头的字符串。对于三方开发者，应用审核时将拒绝以 com.syberos、 syberos 和 com.example. 开头的包名称。 |
| syberos:version     | 版本号。必须是一个正整数。此数值作为内部版本比较用。数值较大的将被认为是更高的版本。这个数值将不会在任何界面展示给用户，用户看到的是 syberos:versionName。                                                                                                                                                                                        |
| syberos:versionName | 版本名称。是一个不超过 32 字符的字符串。不作为版本比较依据，版本比较使用。                                                                                                                                                                                                                                                                        |

#### 示例

```xml
<sopconfig xmlns:syberos="http://schemas.syberos.com/sop/res/syberos/v1"
  syberos:sopid="string"
  syberos:versionCode="integer"
  syberos:versionName="string">
</sopconfig>
```

## application

声明应用的各个组件，如图形应用、服务等

| 属性名              | 描述                     |
| ------------------- | ------------------------ |
| syberos:debuggable  | 是否允许调试，布尔值     |
| syberos:descriotion | 此应用的描述             |
| syberos:icon        | 包含路径应用图标的文件名 |
| syberos:name        | 应用的名称               |

#### 示例

```xml
<application syberos:debuggable="true"
  syberos:description="string"
  syberos:icon="app.png"
  syberos:name="MYAPP" >
</application>
```

## url

仅能在 uiapp 中使用，用来描述 uiapp 可以接受哪些 url。当系统需要处理声明的 scheme 时，将调用此 uiapp

| 属性名         | 描述                        |
| -------------- | --------------------------- |
| syberos:scheme | 描述 uiapp 可以接受哪些 url |

#### 示例

```xml
<url>
  <scheme>string</scheme>
</url>
```

## uses-permission

uses-permission 列出了应用所需要的权限。这些权限将在安装时和用户查看已安装应用时显示给用户，用户可以选择将其中的部分或全部授权给应用。对于此处没有列出的权限和用户没有授权的权限，应用在使用权限时将遇到错误。如果需要申请多个权限，需要写多个并列的 uses-permission 元素

| 属性名                                   | 描述                                                                           |
| ---------------------------------------- | ------------------------------------------------------------------------------ |
| syberos:name                             | 权限的名称字符串                                                               |
| syberos.permission.ACCESS_ALARM          | 允许应用申请 ALARM                                                             |
| syberos.permission.ACCESS_APP_PERMISSION | 允许应用修改应用的权限，不能修改 mdm 配置的权限                                |
| syberos.permission.ACCESS_BLACKLIST      | 允许应用更新系统黑名单                                                         |
| syberos.permission.ACCESS_BLUETOOTH      | 允许应用通过蓝牙进行通讯                                                       |
| syberos.permission.ACCESS_CAMERA         | 请求访问使用照相设备，后台不能拍照                                             |
| syberos.permission.ACCESS_DATA_NETWORK   | 允许应用使用数据连接                                                           |
| syberos.permission.ACCESS_FLASHLIGHT     | 访问闪光灯                                                                     |
| syberos.permission.ACCESS_NOTIFICATION   | 允许应用发送 Notification                                                      |
| syberos.permission.ACCESS_PHONE          | 允许应用接听、拨打电话                                                         |
| syberos.permission.ACCESS_USERAUTH       | 认证服务相关权限                                                               |
| syberos.permission.ACCESS_SIM            | 允许应用访问 SIM 卡信息、修改 pin 码                                           |
| syberos.permission.ACCESS_SMS            | 允许程序发送短信、读系统短信                                                   |
| syberos.permission.ACCESS_STORAGE        | 允许应用访问内置 SDCard 和外置 SDcard                                          |
| syberos.permission.ACCESS_WAKELOCK       | 防止系统休眠                                                                   |
| syberos.permission.ACCESS_WIFI           | 允许应用通过 WIFI 访问网络                                                     |
| syberos.permission.ADMIN_BLUETOOTH       | 允许应用发现和配对蓝牙设备                                                     |
| syberos.permission.ADMIN_DATA_NETWORK    | 允许应用配置数据连接                                                           |
| syberos.permission.ADMIN_PACKAGES        | 允许安装、卸载应用                                                             |
| syberos.permission.ADMIN_TIME            | 允许应用设置系统时间                                                           |
| syberos.permission.ADMIN_VPN             | 允许应用配置 VPN                                                               |
| syberos.permission.ADMIN_WIFI            | 允许应用配置 WIFI 网络、配置 AP 热点                                           |
| syberos.permission.CAPTURE_SCREEN        | 截屏                                                                           |
| syberos.permission.CLEAR_APP_DATA        | 允许删除应用的数据                                                             |
| syberos.permission.DEVICE_DATAFORMAT     | 数据完全删除                                                                   |
| syberos.permission.DEVICE_OTA            | 允许应用发送 OTA 申请                                                          |
| syberos.permission.DEVICE_RECOVERY       | 允许调用恢复出厂设置                                                           |
| syberos.permission.DEVICE_SHUTDOWN       | 请求关闭、重启设备                                                             |
| syberos.permission.MDM                   | 允许数据中心中修改应用的配置项，允许在权限中心中设置应用的权限，设备全局的权限 |
| syberos.permission.READ_CONTACT          | 允许应用读联系人数据，例如元信通                                               |
| syberos.permission.READ_IMEI             | 允许应用访问设备的 IMEI 号                                                     |
| syberos.permission.READ_FINE_LOCATION    | 允许应用访问精确位置(如 GPS)                                                   |
| syberos.permission.READ_NETWORK_STATE    | 允许应用访问网络状态信息                                                       |
| syberos.permission.RECORD                | 允许程序录制音频，后台也能录音                                                 |
| syberos.permission.VIBRATE               | 允许访问振动设备                                                               |

## uses-sdk

应用对平台的兼容性

| 属性名                   | 描述                                                           |
| ------------------------ | -------------------------------------------------------------- |
| syberos:minSdkVersion    | 此应用所能运行的最小版本号，正整数。默认值 1                   |
| syberos:targetSdkVersion | 此应用所运行的目标版本号，正整数。默认取 syberos:minSdkVersion |

#### 示例

```xml
<uses-sdk syberos:minSdkVersion="integer" syberos:targetSdkVersion="integer" />
```

## uiapp

应用程序的表示层。应用程序的每一个图形都是通过一个或多个 uiapp 的扩展实现的，uiapp 使用 QML 语言来布局和显示信息，以及响应用户动作。

| 属性名           | 描述                         |
| ---------------- | ---------------------------- |
| syberos:id       | 用来标识此 uiapp             |
| syberos:exec     | uiapp 对应的可执行文件位置   |
| syberos:splash   | uiapp 对应的 splash 文件位置 |
| syberos:icon     | 包含路径应用图标的文件名     |
| syberos:launcher | 是否在桌面显示图标，布尔值   |
| syberos:name     | 应用的名称                   |

#### 示例

```xml
<uiapp syberos:id="string"
  syberos:exec="string"
  syberos:splash="string"
  syberos:icon="bin/myapp"
  syberos:launcher="true"
  syberos:name="string" >
</uiapp>
```

## doctype

仅能在 uiapp 中使用，用来定义一个 uiapp 可以支持的文档类型。当系统需要处理声明的文档类型时，将调用此 uiapp 打开文档

| 属性名            | 描述                                                          |
| ----------------- | ------------------------------------------------------------- |
| syberos:id        | 用来标识 doctype，将作为参数传给 doctype 处理函数             |
| syberos:name      | 此文档处理程序在用户界面上显示的名称                          |
| syberos:action    | 应用可以执行的操作，有效的值为 view/edit/share(TODO:需要扩展) |
| syberos:mime-type | 文件格式                                                      |
| syberos:extension | 文件扩展名                                                    |

#### 示例

```xml
<doctype syberos:id="jpeg viewer">
  <syberos:name>JPEG Viewer by SyberOS</syberos:name>
  <syberos:action>view</syberos:action>
  <syberos:mime-type>image/jpeg</syberos:mime-type>
  <syberos:extension>jpg</syberos:extension>
  <syberos:extension>jpeg</syberos:extension>
</doctype>
```

## multidoc

仅能在 uiapp 中使用，用来定义一个 uiapp 可以支持同时打开多个文档。当系统需要处理多个文档时，将调用此 uiapp 打开多个文档

| 属性名         | 描述                               |
| -------------- | ---------------------------------- |
| syberos:action | 应用可以执行的操作，有效的值 share |

#### 示例

```xml
<multidoc syberos:id="email sender">
  <syberos:action>share</syberos:action>
</multidoc>
```

## service

应用程序中不可见的工作者。service 组件在运行时没有图形界面，它可以更新数据源，被可以用来处理一些运行长时间的任务或者不需要用户交互的任务。

| 属性名       | 描述                                                              |
| ------------ | ----------------------------------------------------------------- |
| syberos:id   | 用来标识此 service，开发者应保证在同一 sopconfig.xml 中，此值唯一 |
| syberos:exec | uiapp 对应的可执行文件位置                                        |

#### 示例

```xml
<service syberos:id="string"
  syberos:exec="bin/app-service" >
</service>
```

## event

receiver 中包含任意个 event，当系统有制定的事件时，此 service 被执行，且被通知有对应事件

| 属性名        | 描述           |
| ------------- | -------------- |
| syberos:event | 系统的事件名称 |

#### 示例

```xml
<receiver>
  <syberos:event>string</syberos:event>
</receiver>
```

## backup

声明支持系统备份恢复功能。如果不声明 backup，则表示不支持系统备份恢复功能。backup 标签在 application 中不能超过 1 个

| 属性名       | 描述                                 |
| ------------ | ------------------------------------ |
| syberos:exec | 支持系统备份恢复接口的可执行文件位置 |

#### 示例

```xml
<backup syberos:exec="string" />
```
