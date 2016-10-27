#include "gamemodule.h"

#if defined (_WIN32)
#include "windows/windowsgamemodule.h"
#endif

#if defined (__APPLE__)
#include "osx/osxgamemodule.h"
#endif

using namespace Rocket;

GameModule::~GameModule()
{
}

GameModule* GameModule::Load(const char* name)
{
	GameModule* module = nullptr;

#if defined(_WIN32)
	if (module == nullptr)
	{
		Windows::WindowsGameModule* winmodule = new Windows::WindowsGameModule();

		if (winmodule->Create(name))
		{
            module = winmodule;
		}
        else
        {
            delete winmodule;
        }
	}
#endif
    
#if defined(__APPLE__)
    if (module == nullptr)
    {
        OSX::OSXGameModule* osxmodule = new OSX::OSXGameModule();
        
        if (osxmodule->Create(name))
        {
            module = osxmodule;
        }
        else
        {
            delete osxmodule;
        }
    }
#endif

	return module;
}

void GameModule::Unload(GameModule* module)
{
	delete module;
}
