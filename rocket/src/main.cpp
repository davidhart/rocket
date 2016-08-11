#include "gameview.h"

#include <thread>

using namespace Rocket;

int main(char** argv, int argc)
{
	GameView* view = GameView::Create("test application");

	while (view->IsClosed() == false)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		view->FlushEvents();
	}

	GameView::Release(view);

	return 0;
}
