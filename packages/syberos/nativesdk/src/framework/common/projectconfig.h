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
    Q_INVOKABLE QString getLogLevel();
    /**
     * 是否开启debug
     */
    Q_INVOKABLE bool isDebug();
    /**
     * 是否开启热更新
     */
    Q_INVOKABLE bool isUseHot();

    Q_INVOKABLE QString getProjectName();

    Q_INVOKABLE QString getAppName();

    Q_INVOKABLE QString getSopid();

    Q_INVOKABLE QString getTarget();

    Q_INVOKABLE QString getTargetSimulator();
    /**
     * 获取web目录位置
    */
    Q_INVOKABLE QString getWebPath();
    /**
     * 获取首页
     */
    Q_INVOKABLE QString getHomePage();
    /**
     * 获取应用仓库url
     */
    Q_INVOKABLE QString getStoreBaseUrl();
    /**
     * 手机ssh IP
     */
    Q_INVOKABLE QString getDeployIP();
    /**
     * 手机ssh端口
     */
    Q_INVOKABLE QString getDeployPort();
    /**
     * 获取开发服务IP
     */
    Q_INVOKABLE QString getDevServerIP();
    /**
     * 获取开发服务端口
     */
    Q_INVOKABLE QString getDevServerPort();
    /**
     * QtWebengine remote debugging 端口
     */
    Q_INVOKABLE QString getDebuggingPort();

    /**
     * StatusBar 状态
     */
    Q_INVOKABLE bool statusBarShow();

     /**
     * StatusBar Style
     */
    Q_INVOKABLE QString statusBarStyle();

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
