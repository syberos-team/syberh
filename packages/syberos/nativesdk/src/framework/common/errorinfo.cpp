#include "errorinfo.h"

namespace NativeSdk {

static QMap<ErrorInfo::ErrorCode, QString> errors;


ErrorInfo::~ErrorInfo(){
    errors.clear();
}

void ErrorInfo::init(){
    errors.insert(UndefinedModule, "未定义模块");
    errors.insert(ErrorCode::IllegalMediaTypeError, "不合法的媒体文件类型");
    errors.insert(ErrorCode::IllegalFileType, "不合法的文件类型");
    errors.insert(ErrorCode::FileNotExists, "文件不存在");
    errors.insert(ErrorCode::InvalidURLError, "无效的url");
    errors.insert(ErrorCode::NotEnoughSpace, "空间不足");
    errors.insert(ErrorCode::InvalidFilePermission, "文件无操作权限");
    errors.insert(ErrorCode::InvalidParameter, "参数错误");
    errors.insert(ErrorCode::SystemError, "系统错误");
    errors.insert(ErrorCode::NetworkError, "网络错误");
    errors.insert(ErrorCode::InvalidPermission, "权限错误");
    errors.insert(ErrorCode::InvalidCall, "无效的调用");
    errors.insert(ErrorCode::UnknowError, "未知的错误");

}

QString ErrorInfo::message(ErrorInfo::ErrorCode code){
    return errors.value(code);
}

QString ErrorInfo::message(ErrorInfo::ErrorCode code, const QString &msg){
    QString errorMsg = errors.value(code);
    if(errorMsg.isEmpty()){
        return QString(msg);
    }
    return QString("%1: %2").arg(errorMsg, msg);
}

}
