#ifndef SENVIRONMENT_H
#define SENVIRONMENT_H

#include "nativesdk_global.h"

#include <QObject>
#include <cenvironment.h>

namespace NativeSdk {

class NATIVESDK_EXPORT SEnvironment : public CEnvironment
{
    Q_OBJECT
public:
  SEnvironment();
  ~SEnvironment();

  Q_INVOKABLE float dp(int num);
};

}
#endif // SENVIRONMENT_H
