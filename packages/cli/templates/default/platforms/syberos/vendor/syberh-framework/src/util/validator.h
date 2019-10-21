#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QObject>

class Validator : public QObject
{
public:
    /**
     * @brief isHttpUrl 判断是否http请求url
     * @param url
     * @return
     */
    static bool isHttpUrl(const QString &url);

private:
    explicit Validator(QObject *parent = 0);
    Validator(const Validator &) Q_DECL_EQ_DELETE;
    Validator& operator=(Validator validator) Q_DECL_EQ_DELETE;
};

#endif // VALIDATOR_H
