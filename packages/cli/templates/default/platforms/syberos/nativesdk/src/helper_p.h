#ifndef HELPER_P_H
#define HELPER_P_H

#include <cenvironment.h>

namespace NativeSdk {

namespace Internal{

class HelperPrivate {
public:
    ~HelperPrivate();

    CEnvironment *env;
};

} // namespace Internal
} // namespace NativeSdk

#endif // HELPER_P_H
