#include "path.h"
#include "helper.h"
#include <QJsonObject>

int Path::typeId = qRegisterMetaType<Path *>();

Path::Path()
{
}
Path::~Path()
{

}

void Path::request(QString callBackID, QString actionName, QVariantMap params)
{
    Q_UNUSED(params);

    if (actionName == "extern") {
        getExternStorageRootPath(callBackID);
    } else if (actionName == "inner") {
        getInnerStorageRootPath(callBackID);
    } else if (actionName == "dataRoot"){
        getDataRootPath(callBackID);
    }
}

void Path::getExternStorageRootPath(QString callBackID)
{
    Helper *helper = Helper::instance();
    QString ext = helper->getExternStorageRootPath();
    QJsonObject jsObj;
    jsObj.insert("result", ext);
    emit success(callBackID.toLong(), jsObj);
}
void Path::getInnerStorageRootPath(QString callBackID)
{
    Helper *helper = Helper::instance();
    QString inner = helper->getInnerStorageRootPath();
    QJsonObject jsObj;
    jsObj.insert("result", inner);
    emit success(callBackID.toLong(), jsObj);
}
void Path::getDataRootPath(QString callBackID)
{
    Helper *helper = Helper::instance();
    QString dataRoot = helper->getDataRootPath();
    QJsonObject jsObj;
    jsObj.insert("result", dataRoot);
    emit success(callBackID.toLong(), jsObj);
}
