#pragma once
#ifndef ROCKET_GAMEMODULE_INCLUDED
#define ROCKET_GAMEMODULE_INCLUDED

#include "api.h"

namespace Rocket
{
	class Game;
	class Renderer;

	typedef Game*(*GameModuleCreateProc)(Renderer* renderer);
	typedef void(*GameModuleReleaseProc)(Game*);

	class GameModule
	{
	public:
		ROCKET_API static GameModule* Load(const char* name);
		ROCKET_API static void Unload(GameModule* module);

		virtual ~GameModule();

		virtual Game* CreateGame(Renderer* renderer) = 0;
		virtual void ReleaseGame(Game* game) = 0;
	};
}

#endif