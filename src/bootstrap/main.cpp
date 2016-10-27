#include "gameview.h"
#include "renderer.h"
#include "gamemodule.h"
#include "game.h"

#include <thread>
#include <cassert>
#include <chrono>
#include <iostream>

using namespace Rocket;
using namespace std::chrono;

int main(int argc, char** argv)
{
	const char* game_module = "example_game";
	if (argc == 2) game_module = argv[1];

	GameView* view = GameView::Create("test application");
    assert(view);
    view->SetIsResizable(true);
    
    Renderer* renderer = view->CreateRenderer();
    assert(renderer);

	GameModule* module = GameModule::Load(game_module);
	assert(module);

	Game* game = module->CreateGame(renderer);
	
    steady_clock::time_point prevTime = steady_clock::now();

	while (view->IsClosed() == false)
	{
		std::this_thread::sleep_for(seconds(0));

        steady_clock::time_point currentTime = steady_clock::now();
		
		view->FlushEvents();

        duration<float> delta = duration<float>(currentTime - prevTime);

		game->Update(delta.count());

		renderer->Present();

		prevTime = currentTime;
	}

	module->ReleaseGame(game);

	GameModule::Unload(module);

	view->ReleaseRenderer(renderer);
	GameView::Release(view);
	
	return 0;
}
