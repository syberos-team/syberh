---
title: APP 配置
---

所有权限均在在sopconfig.xml文件中配置


## sopconfig 结构
``` XML
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
            <htmlapp>
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
            </htmlapp>
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

## sopconfig 配置解读


### sopconfig 
sopconfig 是 sopconfig.xml 的根元素

| 属性名     |描述                             |
| ---------- |---------------------------------------- |
| syberos     |   命名空间   |
| sopid     |   包名称   |
| version     |  版本号，正整数   |
| versionName     |  版本名称   |

代码示例
``` XML
<sopconfig xmlns:syberos="http://schemas.syberos.com/sop/res/syberos/v1"
  syberos:sopid="string"
  syberos:versionCode="integer"
  syberos:versionName="string">
  . . .
</sopconfig>
```

### uses-permission 
uses-permission 列出了应用所需要的权限。这些权限将在安装时和用户查看已安装应用时显示给用户，用户可以选择将其中的部分或全部授权给应用。对于此处没有列出的权限和用户没有授权的权限，应用在使用权限时将遇到错误。如果需要申请多个权限，需要写多个并列的uses-permission元素。
| 属性名     |  描述                                    |
| ---------- |---------------------------------------- |
| syberos:name     |  权限的名称字符串   |
| syberos.permission.ACCESS_ALARM |允许应用申请ALARM |
| syberos.permission.ACCESS_APP_PERMISSION |允许应用修改应用的权限，不能修改mdm配置的权限 |
| syberos.permission.ACCESS_BLACKLIST |允许应用更新系统黑名单 |
| syberos.permission.ACCESS_BLUETOOTH |允许应用通过蓝牙进行通讯 |
| syberos.permission.ACCESS_CAMERA |请求访问使用照相设备，后台不能拍照 |
| syberos.permission.ACCESS_DATA_NETWORK |允许应用使用数据连接 |
| syberos.permission.ACCESS_FLASHLIGHT |访问闪光灯 |
| syberos.permission.ACCESS_NOTIFICATION |允许应用发送Notification |
| syberos.permission.ACCESS_PHONE |允许应用接听、拨打电话 |
| syberos.permission.ACCESS_USERAUTH |认证服务相关权限 |
| syberos.permission.ACCESS_SIM |允许应用访问SIM卡信息、修改pin码 |
| syberos.permission.ACCESS_SMS |允许程序发送短信、读系统短信 |
| syberos.permission.ACCESS_STORAGE |允许应用访问内置SDCard和外置SDcard |
| syberos.permission.ACCESS_WAKELOCK |防止系统休眠 |
| syberos.permission.ACCESS_WIFI |允许应用通过WIFI访问网络 |
| syberos.permission.ADMIN_BLUETOOTH |允许应用发现和配对蓝牙设备 |
| syberos.permission.ADMIN_DATA_NETWORK |允许应用配置数据连接 |
| syberos.permission.ADMIN_PACKAGES |允许安装、卸载应用 |
| syberos.permission.ADMIN_TIME |允许应用设置系统时间 |
| syberos.permission.ADMIN_VPN |允许应用配置VPN |
| syberos.permission.ADMIN_WIFI |允许应用配置WIFI网络、配置AP热点 |
| syberos.permission.CAPTURE_SCREEN |截屏 |
| syberos.permission.CLEAR_APP_DATA |允许删除应用的数据 |
| syberos.permission.DEVICE_DATAFORMAT |数据完全删除 |
| syberos.permission.DEVICE_OTA |允许应用发送OTA申请 |
| syberos.permission.DEVICE_RECOVERY |允许调用恢复出厂设置 |
| syberos.permission.DEVICE_SHUTDOWN |请求关闭、重启设备 |
| syberos.permission.MDM |允许数据中心中修改应用的配置项，允许在权限中心中设置应用的权限，设备全局的权限 |
| syberos.permission.READ_CONTACT |允许应用读联系人数据，例如元信通 |
| syberos.permission.READ_IMEI |允许应用访问设备的IMEI号 |
| syberos.permission.READ_FINE_LOCATION |允许应用访问精确位置(如GPS) |
| syberos.permission.READ_NETWORK_STATE |允许应用访问网络状态信息 |
| syberos.permission.RECORD |允许程序录制音频，后台也能录音 |
| syberos.permission.VIBRATE |允许访问振动设备 |

### uses-sdk 
应用对平台的兼容性

| 属性名     |  描述                                    |
| ---------- |---------------------------------------- |
| minSdkVersion     |  此应用所能运行的最小版本号，正整数。默认值1   |
| targetSdkVersion     |  此应用所运行的目标版本号，正整数。默认取syberos:minSdkVersion  |

代码示例
``` XML
<uses-sdk syberos:minSdkVersion="integer" syberos:targetSdkVersion="integer" />
```

### application
声明应用的各个组件，如图形应用、服务等

| 属性名     |  描述                                    |
| ---------- |---------------------------------------- |
| debuggable     |  是否允许调试，布尔值   |
| descriotion     |  此应用的描述   |
| icon     |  包含路径应用图标的文件名   |
| name     |  应用的名称   |

``` XML
<application syberos:debuggable=["true" | "false"]
  syberos:description="string"
  syberos:icon="path/to/icon/file"
  syberos:name="string" >
  . . .
</application>
```
### uiapp 
声明一个包含用户图形交互的应用模块

| 属性名     |  描述                                    |
| ---------- |---------------------------------------- |
| id     |  用来标识此 uiapp   |
| exec     |  uiapp 对应的可执行文件位置   |
| splash     |  uiapp 对应的splash文件位置   |
| icon     |  包含路径应用图标的文件名   |
| launcher     |  是否在桌面显示图标，布尔值   |
| name     |  应用的名称   |


``` XML
<uiapp syberos:id="string"
  syberos:exec="string"
  syberos:splash="string"
  syberos:icon="path/to/icon/file"
  syberos:launcher=["true" | "false"]
  syberos:name="string" >
  . . .
</uiapp>
```
### htmlapp
声明一个包含用户图形交互的应用模块

| 属性名     |  描述                                    |
| ---------- |---------------------------------------- |
| id     |  用来标识此 uiapp   |
| exec     |  uiapp 对应的可执行文件位置   |
| splash     |  uiapp 对应的splash文件位置   |
| icon     |  包含路径应用图标的文件名   |
| launcher     |  是否在桌面显示图标，布尔值   |
| name     |  应用的名称   |


``` XML
<htmlapp syberos:id="string"
  syberos:exec="string"
  syberos:splash="string"
  syberos:icon="path/to/icon/file"
  syberos:launcher=["true" | "false"]
  syberos:name="string" >
  . . .
</htmlapp>
```

### url
仅能在 uiapp 中使用，用来描述 uiapp 可以接受哪些 url。当系统需要处理声明的 scheme 时，将调用此 uiapp

| 属性名     |  描述                                    |
| ---------- |---------------------------------------- |
| scheme     |  描述 uiapp 可以接受哪些 url   |

``` XML
<url>
  <scheme>string</scheme>
</url>
```

### doctype
仅能在 uiapp 中使用，用来定义一个 uiapp 可以支持的文档类型。当系统需要处理声明的文档类型时，将调用此 uiapp 打开文档

| 属性名     |  描述                                    |
| ---------- |---------------------------------------- |
| id     |   用来标识 doctype，将作为参数传给 doctype 处理函数  |
| name     |  此文档处理程序在用户界面上显示的名称   |
| action     |  应用可以执行的操作，有效的值为view/edit/share(TODO:需要扩展)   |
| mime-type     |  文件格式  |
| extension     |  文件扩展名   |

``` XML
<doctype id="jpeg viewer">
  <name>JPEG Viewer by SyberOS</name>
  <action>view</action>
  <mime-type>image/jpeg</mime-type>
  <extension>jpg</extension>
  <extension>jpeg</extension>
</doctype>
```

### multidoc
仅能在 uiapp 中使用，用来定义一个 uiapp 可以支持同时打开多个文档。当系统需要处理多个文档时，将调用此 uiapp 打开多个文档

| 属性名     |  描述                                    |
| ---------- |---------------------------------------- |
| action     |  应用可以执行的操作，有效的值share   |

``` XML
<multidoc id="email sender">
  <action>share</action>
</multidoc>
```

### service
声明一个服务模块

| 属性名     |  描述                                    |
| ---------- |---------------------------------------- |
| id     |  用来标识此 service，开发者应保证在同一 sopconfig.xml 中，此值唯一   |
| exec     |  uiapp 对应的可执行文件位置   |

``` XML
<service syberos:id="string"
  syberos:exec="string" >
  . . .
</service>
```

### event
receiver 中包含任意个 event，当系统有制定的事件时，此 service 被执行，且被通知有对应事件

| 属性名     |  描述                                    |
| ---------- |---------------------------------------- |
| event     |  系统的事件名称   |

``` XML
<receiver>
  <event>string</event>
</receiver>
```

### backup
声明支持系统备份恢复功能。如果不声明 backup，则表示不支持系统备份恢复功能。backup 标签在 application 中不能超过1个

| 属性名     |  描述                                    |
| ---------- |---------------------------------------- |
| exec     |  支持系统备份恢复接口的可执行文件位置   |

``` XML
<backup syberos:exec="string" />
```
