#include "gameview.h"
#include "windowsgameviewimpl.h"

GameView* GameView::Create(const char* title)
{
	IGameViewImpl* impl = new WindowsGameViewImpl();

	if (impl->Create() == false)
	{
		delete impl;
		return nullptr;
	}

	return new GameView(impl);
}

void GameView::SetTitle(const char* title)
{
	impl->SetTitle(title);
}

void GameView::Release(GameView* view)
{
	delete view;
}

GameView::GameView(IGameViewImpl* impl) : 
	impl(impl)
{

}

GameView::~GameView()
{

}