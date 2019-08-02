# Get Started

## 环境配置

首先需要安装[Node.js](https://nodejs.org/en/)，并配置环境变量

修改npm源
```shell
npm config set registry https://registry.npm.taobao.org
```

本项目使用[Yarn](https://yarn.bootcss.com/)

安装yarn
```shell
npm install -g yarn
```

本项目使用[lerna](https://github.com/lerna/lerna#readme)

安装lerna
```shell
npm install lerna -g
```

## 安装依赖

```shell
lerna bootstrap
```

## 启动环境

运行开发环境
```shell
lerna run dev
```
