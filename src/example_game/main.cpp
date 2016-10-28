#include "bootstrap.h"
#include "examplegame.h"

using namespace Rocket;

int main(int, char**)
{
    Bootstrap bootstrap;
    bootstrap.Start("example_game");
    ExampleGame game(bootstrap.GetRenderer());
    return bootstrap.Run(&game);
}
