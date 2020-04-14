---
title: vue项目使用syberh
---

前提: 使用[@vue/cli](https://cli.vuejs.org/zh/)创建项目

## 如何在项目中使用syberh
- 安装syberh和vconsole的包
```bash
$ npm i @syberos/jsbridge vconsole
```

- 在`src/main.js`中引用
```javascript
  import syberh from '@syberos/jsbridge'
  import VConsole from 'vconsole/dist/vconsole.min.js'

  // 注册到window对象上，可以全局使用
  window.syberh = syberh
  window.vConsole = new VConsole()
```

- 在`.vue`文件中使用
```javascript
<template>
    <div @click="modalAlert">点我弹框</div>
</template>

<script>
export default {
  methods: {
    modalAlert() {
      syberh.modal.alert({
        content: 'This is a alert',
        success: function() {
            console.log('success');            
        },
        fail: function(error) {
            console.log('fail: ', error.code, error.msg);
        }
      })
    }
  }
}
</script>
```

## 打包注意事项

在syberh中的项目, 文件路径需要是相对路径
  
在根目录下新建`vue.config.js`, 配置如下代码
```javascript
  module.exports = {
      // 生产环境打包出来,资源路径是相对路径
      publicPath: process.env.NODE_ENV === 'production' ? './' : '/'
  }
```

打包
```bash
$  yarn build
```

## 打包后怎么跑起来
创建一个syberh示例项目

```bash
$ syberh init --example
$ ls
  www node_modules  package.json  platforms  project.config.json  yarn.lock
```

把`VUE项目`打包后的目录(一般是`dist`),拷贝到`syberh项目`根目录下
```bash
$ ls
  dist www node_modules  package.json  platforms  project.config.json  yarn.lock
```

修改`project.config.json`相关配置项
```javascript
{
  # 修改项目的www目录（默认是根目录下www目录）
  "webPath": "dist"
}
```

运行syberh项目
```javascript
$ yarn run build:device
```

## 示例项目下载
https://syberos.yuque.com/docs/share/91f42378-96e1-490e-9edd-c4eedd031d43?#（密码：dxqv）