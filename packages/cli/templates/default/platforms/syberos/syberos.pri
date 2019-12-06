QML_IMPORT_PATH = $$[QT_INSTALL_QML]

# This is needed for using syberos-application and syberos-qt module
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../syberos_application \
			   $$[QT_INSTALL_HEADERS]/../framework

#Please Do not modify these macros, otherwise your app will not installed correctly and will not run at all.
APP_DIR = /data/apps
APP_DATA = /data/data
INSTALL_DIR = $$APP_DIR/com.syberos.demo
DATA_DIR = $$APP_DATA/com.syberos.demo

LIB_DIR = /data/app-libs/com.syberos.demo

DEFINES += SOP_ID=\\\"com.syberos.demo\\\"
DEFINES += APP_DIR_ENVVAR=\\\"APPDIR_REGULAR\\\"
# Currently home screen sets the environment variable, so wen run from
# elsewhere, use this work-around instead.
DEFINES += APP_DIR=\\\"$$APP_DIR\\\"
