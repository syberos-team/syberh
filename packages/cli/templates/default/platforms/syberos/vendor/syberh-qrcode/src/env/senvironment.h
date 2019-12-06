#ifndef SENVIRONMENT_H
#define SENVIRONMENT_H
#include <QObject>
#include <cenvironment.h>


class SEnvironment : public CEnvironment
{
    Q_OBJECT
public:
  SEnvironment();
  ~SEnvironment();
  Q_INVOKABLE float dp(int num);
};

#endif // SENVIRONMENT_H
