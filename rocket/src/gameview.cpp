#include "gameview.h"
#include "windowsgameviewimpl.h"

using namespace Rocket;

GameView* GameView::Create(const char* title)
{
	IGameViewImpl* impl = new Windows::WindowsGameViewImpl();

	if (impl->Create() == false)
	{
		delete impl;
		return nullptr;
	}

	impl->SetTitle(title);

	return new GameView(impl);
}

void GameView::SetTitle(const char* title)
{
	m_impl->SetTitle(title);
}

void GameView::Release(GameView* view)
{
	delete view;
}

void GameView::FlushEvents()
{
	m_impl->FlushEvents();
}

bool GameView::IsClosed()
{
	return m_impl->IsClosed();
}

GameView::GameView(IGameViewImpl* impl) : 
	m_impl(impl)
{

}

GameView::~GameView()
{

}