#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#include <QObject>

#include "../../nativesdk_global.h"
#include "projectconfig_p.h"

namespace NativeSdk {

class ProjectConfigPrivate;

/**
 * 读取project.config.json中的内容并缓存
 */
class NATIVESDK_EXPORT ProjectConfig : public QObject
{
    Q_OBJECT
public:
    virtual ~ProjectConfig();

    static ProjectConfig *instance();
    /**
     * 获取日志级别
     */
    QString getLogLevel();
    /**
     * 是否开启debug
     */
    bool isDebug();

    QString getProjectName();

    QString getAppName();

    QString getSopid();

    QString getTarget();

    QString getTargetSimulator();
    /**
     * 获取web目录位置
     */
    QString getWebPath();
    /**
     * 获取首页
     */
    QString getHomePage();
    /**
     * 获取应用仓库url
     */
    QString getStoreBaseUrl();
    /**
     * 手机ssh IP
     */
    QString getDeployIP();
    /**
     * 手机ssh端口
     */
    QString getDeployPort();
    /**
     * 获取开发服务IP
     */
    QString getDevServerIP();
    /**
     * 获取开发服务端口
     */
    QString getDevServerPort();
    /**
     * QtWebengine remote debugging 端口
     */
    QString getDebuggingPort();

private:
    explicit ProjectConfig(QObject *parent = nullptr);
    ProjectConfig(const ProjectConfig &) Q_DECL_EQ_DELETE;
    ProjectConfig &operator=(ProjectConfig config) Q_DECL_EQ_DELETE;

    void load();

    static ProjectConfig *_instance;
    ProjectConfigPrivate *d = nullptr;
};

}
#endif // PROJECT_CONFIG_H
