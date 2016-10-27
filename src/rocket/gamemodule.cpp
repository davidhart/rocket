#include "gamemodule.h"

#if defined (_WIN32)
#include "windows/windowsgamemodule.h"
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

		if (winmodule->Create(name) == false)
		{
			delete winmodule;
		}

		module = winmodule;
	}
#endif

	return module;
}

void GameModule::Unload(GameModule* module)
{
	delete module;
}
