#include "errorinfo.h"
QMap<int,QString> ErrorInfo::m_errorCode ;
ErrorInfo::ErrorInfo(){
   m_errorCode.insert(NETWORK_ERROR,"网络错误");
}
ErrorInfo::~ErrorInfo(){}

