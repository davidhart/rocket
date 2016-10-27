#if defined(__APPLE__)

#include "osx/osxgamemodule.h"
#include <dlfcn.h>
#include <string>
#include <cassert>

using namespace Rocket;
using namespace Rocket::OSX;

OSXGameModule::OSXGameModule() :
    m_handle(nullptr),
    m_createproc(nullptr),
    m_releaseproc(nullptr)
{
    
}

OSXGameModule::~OSXGameModule()
{
    if (m_handle)
        dlclose(m_handle);
}

bool OSXGameModule::Create(const char *name)
{
    std::string realname = std::string(name);
    
    m_handle = dlopen(realname.c_str(), RTLD_LAZY);
    assert(m_handle);
    
    if (m_handle == nullptr)
        return false;
    
    m_createproc = (GameModuleCreateProc)dlsym(m_handle, "CreateGame");
    assert(m_createproc);
    
    m_releaseproc = (GameModuleReleaseProc)dlsym(m_handle, "ReleaseGame");
    assert(m_releaseproc);
    
    return (m_createproc != nullptr) && (m_releaseproc != nullptr);
}

Game* OSXGameModule::CreateGame(Renderer *renderer)
{
    return m_createproc(renderer);;
}

void OSXGameModule::ReleaseGame(Game *game)
{
    m_releaseproc(game);
    
}

#endif
