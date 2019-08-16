#ifndef MULTIMEDIAUTILS_H
#define MULTIMEDIAUTILS_H
#include <QString>
#include<QObject>
/**
 * @brief The MultimediaUtils class : 多媒体模块的实用工具类
 */

class MultimediaUtils : public QObject
{
    Q_OBJECT
public:
    static MultimediaUtils* getInstance();
    ~MultimediaUtils();
    Q_INVOKABLE QString getMultimediaSavePath() const;
    Q_INVOKABLE void removeMultimediaFile(const QStringList &multimediaFlieList, const bool all = true);
    Q_INVOKABLE QString scaledImage(const QString &imgPath);
    Q_INVOKABLE void imgTransformed(const QString &imgPath);
private:
    MultimediaUtils(QObject *parent = 0);
    static MultimediaUtils* m_pMultimediaUtils;
    QString m_nMultiMediaPath;
};

#endif // MULTIMEDIAUTILS_H
