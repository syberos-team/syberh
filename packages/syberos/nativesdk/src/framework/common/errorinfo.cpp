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
    errors.insert(ErrorCode::IllegalFileSize, "不合法的文件大小");
    errors.insert(ErrorCode::IllegalMediaId, "不合法的媒体文件 id");
    errors.insert(ErrorCode::IllegalImageSize, "不合法的图片文件大小");
    errors.insert(ErrorCode::IllegalVoiceSize, "不合法的语音文件大小");
    errors.insert(ErrorCode::IllegalVideoSize, "不合法的视频文件大小");
    errors.insert(ErrorCode::IllegalThumbnailSize, "不合法的缩略图文件大小");
    errors.insert(ErrorCode::InvalidType, "类型错误");
    errors.insert(ErrorCode::UnsupportedImage, "不支持的图片格式");
    errors.insert(ErrorCode::IllegalRequestFormat, "不合法的请求格式");
    errors.insert(ErrorCode::IllegalUrlSize, "不合法的 URL 长度");
    errors.insert(ErrorCode::FileNotExists, "文件不存在");
    errors.insert(ErrorCode::InvalidURLError, "无效的url");
    errors.insert(ErrorCode::UploadFileMissing, "上传文件缺失");
    errors.insert(ErrorCode::IllegalUploadFileType, "上传素材的文件类型不合法");
    errors.insert(ErrorCode::IllegalUploadFileSize, "上传素材的文件尺寸不合法");
    errors.insert(ErrorCode::UploadFileFailed, "上传失败");
    errors.insert(ErrorCode::CannelFailed, "取消失败");
    errors.insert(ErrorCode::NotEnoughSpace, "空间不足");
    errors.insert(ErrorCode::InvalidFilePermission, "文件无操作权限");
    errors.insert(ErrorCode::InvalidParameter, "参数错误");
    errors.insert(ErrorCode::SystemError, "系统错误");
    errors.insert(ErrorCode::NetworkError, "网络错误");
    errors.insert(ErrorCode::InvalidPermission, "权限错误");
    errors.insert(ErrorCode::InvalidCall, "无效的调用");
    errors.insert(ErrorCode::UnknowError, "未知的错误");
    errors.insert(ErrorCode::databaseError, "数据库错误");

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
