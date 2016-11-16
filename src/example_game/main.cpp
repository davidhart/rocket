#include "examplegame.h"

using namespace Rocket;

int main(int, char**)
{
    ExampleGame game;
    return Game::Bootstrap(&game);
}
