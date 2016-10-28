#pragma once
#ifndef ROCKET_BOOTSTRAP_INCLUDED
#define ROCKET_BOOTSTRAP_INCLUDED

#include "api.h"

namespace Rocket
{
    class Game;
    class GameView;
    class Renderer;

    class Bootstrap
    {
    public:
        ROCKET_API Bootstrap();
        ROCKET_API ~Bootstrap();
        ROCKET_API bool Start(const char* name);
        ROCKET_API void Run(Game* game);

        ROCKET_API Renderer* GetRenderer();
        ROCKET_API GameView* GetGameView();

    private:
        GameView* m_view;
        Renderer* m_renderer;
    };
}

#endif