#include "bootstrap.h"
#include "examplegame.h"

using namespace Rocket;

int main(int, char**)
{
    Bootstrap bootstrap;
    bootstrap.Start("example_game");
    ExampleGame game;
    game.InitView(bootstrap.GetGameView());
    game.InitGraphics(bootstrap.GetRenderer());
    return bootstrap.Run(&game);
}
