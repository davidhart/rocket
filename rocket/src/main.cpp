#include "gameview.h"

#include <thread>

using namespace Rocket;

int main(char** argv, int argc)
{
	GameView* view = GameView::Create("test application");
	Renderer* renderer = view->CreateRenderer();
	
	view->SetIsResizable(true);

	while (view->IsClosed() == false)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(0));
		view->FlushEvents();
	}
	
	view->ReleaseRenderer(renderer);
	GameView::Release(view);
	
	return 0;
}
