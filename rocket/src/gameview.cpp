#include "gameview.h"
#include "windowsgameview.h"

using namespace Rocket;

GameView* GameView::Create(const char* title)
{
	Windows::WindowsGameView* view = new Windows::WindowsGameView();

	if (view->Create() == false)
	{
		delete view;
		return nullptr;
	}

	view->SetTitle(title);

	return view;
}

void GameView::Release(GameView* view)
{
	delete view;
}

GameView::~GameView()
{

}