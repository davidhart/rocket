#pragma once
#ifndef ROCKET_GAME_INCLUDED
#define ROCKET_GAME_INCLUDED

#include "api.h"

namespace Rocket
{
	class Game
	{
	public:
		virtual void Update(float dt) = 0;
	};
}

#endif