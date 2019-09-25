#include "errorinfo.h"

static QMap<ErrorInfo::ErrorCode, QString> m_error;


ErrorInfo::~ErrorInfo(){
    m_error.clear();
}

void ErrorInfo::init(){
    if(!m_error.isEmpty()){
        return;
    }

    m_error.insert(ErrorCode::NetworkError, "网络错误");
    m_error.insert(ErrorCode::UnknowError, "未知的错误");
}

QString ErrorInfo::getErrorMessage(ErrorInfo::ErrorCode code){
    init();
    return m_error.value(code);
}

