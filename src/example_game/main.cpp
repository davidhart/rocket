#include "bootstrap.h"
#include "examplegame.h"

using namespace Rocket;

int main(int, char**)
{
    Bootstrap bootstrap;
    bootstrap.Start("example_game");

    Game* game = new ExampleGame(bootstrap.GetRenderer());
	
    bootstrap.Run(game);

    delete game;

	return 0;
}
