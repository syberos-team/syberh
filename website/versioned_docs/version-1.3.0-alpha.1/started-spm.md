---
title: spm 工具
id: version-1.3.0-alpha.1-started-spm
original_id: started-spm
---

spm 工具是为 syberos 开发的包管理工具。

目前，spm 工具仍在完善中，最新版本 [点击此处](https://spm.syberos.com/download?version=latest) 下载。

## 安装

使用以下命令完成最新版本 spm 的安装

```bash
# 使用curl下载并安装
curl -o spm https://spm.syberos.com/download?version=latest && sudo install -m 755 ./spm /usr/local/bin/

# 使用wget下载并安装
wget -O spm https://spm.syberos.com/download?version=latest && sudo install -m 755 ./spm /usr/local/bin/
```

## 使用

spm 功能使用子命令方式提供调用，示例如下

```bash
# 查询仓库中包含syberh的包
spm search syberh
```

### init

创建可由 spm 管理的项目

```bash
spm init
```

### search

模糊查询指定的包

```bash
spm search syberh
```

### info

查询指定包的信息，参数是完整的包名

```bash
spm info syberh.framework
```

### install

安装依赖包

```bash
# 安装依赖包syberh.framework最新版本
spm install syberh.framework
# 安装依赖包syberh.framework指定版本
spm install syberh.framework@1.0.0
```

### uninstall

卸载依赖包（实现中）

### publish

发布包

```bash
spm publish
```

### upgrade

更新 spm

注意：可能需要使用root权限

```bash
spm upgrade
```
