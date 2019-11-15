#include "App_Workspace.h"


Q_DECL_EXPORT int main(int argc, char *argv[])
{
    // QT版本大于5.6，给webengine加参数启动
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    std::vector<char*> new_argv(argv, argv + argc);
    new_argv.push_back(const_cast<char *>("--ignore-gpu-blacklist"));
    new_argv.push_back(nullptr);
    argv = new_argv.data();
    argc = argc + 1;
    #endif

    return SYBEROS::SyberosGuiCache::qApplication(argc, argv, new App_Workspace());
}
