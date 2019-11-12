#include "App_Workspace.h"


Q_DECL_EXPORT int main(int argc, char *argv[])
{
    std::vector<char*> new_argv(argv, argv + argc);
    new_argv.push_back(const_cast<char *>("--ignore-gpu-blacklist"));
    new_argv.push_back(nullptr);
    argv = new_argv.data();
    argc = argc + 1;
    return SYBEROS::SyberosGuiCache::qApplication(argc, argv, new App_Workspace());
}
