# 说明

原 com 目录下的代码现已抽离至 `git@github.com:syberos-team/syberh-framework.git`。

现在 `syberh/packages/syberos` 目录下已没有 com 子目录，多了 vendor 目录，vendor 目录下存放的是子模块的导入文件 vendor.pri。

vendor 目录已添加至 .gitignore。


# 第一次 clone syberh

1. clone syberh 项目后，需要手动创建 vendor 目录（目录位置 `syberh/packages/syberos/vendor`）并在 vendor 目录下新建 vendor.pri 文件。

2. clone syberh-framework 在 vendor 目录中，并在 vendor/vendor.pri 中添加 syberh-framework 项目。

```
INCLUDEPATH += $$PWD
QML_IMPORT_PATH += $$PWD
include($$PWD/syberh-framework/syberh_framework.pri)
```

## 目录结构

```
 + syberos
 | + app
 | + META-INF
 | + script
 | + tests
 | + vendor
   | + syberh-framework
   | - vendor.pri
 | - app.pro
 | - syberos.pri
 | - sopconfig.xml
 ...
```


# 使用 syber IDE

正常启动即可

# 其他说明

也可以将子模块代码下载至其他目录中，然后在 `syberh/packages/syberos/vendor/vendor.pri` 中 include 子模块即可。




