#pragma once
#ifndef ROCKET_WINDOWSGAMEMODULE_INCLUDED
#define ROCKET_WINDOWSGAMEMODULE_INCLUDED

#include "gamemodule.h"
#include <Windows.h>

namespace Rocket
{
	namespace Windows
	{
		class WindowsGameModule : public GameModule
		{
		public:
			WindowsGameModule();
			~WindowsGameModule();

			bool Create(const char* name);

			virtual Game* CreateGame(Renderer* renderer);
			virtual void ReleaseGame(Game* game);

		private:
			HMODULE m_module;
			GameModuleCreateProc m_createproc;
			GameModuleReleaseProc m_releaseproc;
		};
	}
}

#endif