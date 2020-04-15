#-------------------------------------------------
#
# Project generated by QtCreator for SyberOS.
#
#-------------------------------------------------
include (syberos.pri)
TEMPLATE = subdirs

CONFIG += C++11

SUBDIRS += app pluginmanager nativesdk tests

nativesdk.depends = pluginmanager
app.depends = nativesdk

res.files = res
res.path = $$INSTALL_DIR/

meta.files = META-INF
meta.path = $$INSTALL_DIR/

syber.files = sopconfig.xml
syber.path = $$INSTALL_DIR/

lib.files = $$OUT_PWD/lib
lib.path = $$INSTALL_DIR/

plugins.files = plugins
plugins.path = $$INSTALL_DIR/

INSTALLS += res meta syber lib plugins
