#pragma once
#ifndef ROCKET_GAME_INCLUDED
#define ROCKET_GAME_INCLUDED

#include "api.h"

namespace Rocket
{
    class Renderer;
    class GameView;

    class GameServices
    {
    public:
        virtual Renderer* Renderer() = 0;
        virtual GameView* GameView() = 0;
    };

	class Game
	{
	public:
        virtual void Startup(GameServices* services) = 0;
        virtual void Shutdown(GameServices* services) = 0;
		virtual void Update(float dt) = 0;

        static ROCKET_API int Bootstrap(Game* game);
	};
}

#endif