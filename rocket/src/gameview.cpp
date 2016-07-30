#include "gameview.h"
#include "windowsgameviewimpl.h"

GameView* GameView::Create(const wchar_t* title)
{
	IGameViewImpl* impl = new WindowsGameViewImpl();

	if (impl->Create() == false)
	{
		delete impl;
		return nullptr;
	}

	return new GameView(impl);
}

void GameView::SetTitle(const wchar_t* title)
{
	impl->SetTitle(title);
}

void GameView::Release(GameView* view)
{
	delete view;
}

void GameView::FlushEvents()
{
	impl->FlushEvents();
}

bool GameView::IsClosed()
{
	return impl->IsClosed();
}

GameView::GameView(IGameViewImpl* impl) : 
	impl(impl)
{

}

GameView::~GameView()
{

}