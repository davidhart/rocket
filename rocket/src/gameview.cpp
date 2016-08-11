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

Renderer* GameView::CreateRenderer()
{
	return m_impl->CreateRenderer();
}

void GameView::ReleaseRenderer(Renderer* renderer)
{
	m_impl->ReleaseRenderer(renderer);
}

void GameView::FlushEvents()
{
	m_impl->FlushEvents();
}

bool GameView::IsClosed()
{
	return m_impl->IsClosed();
}

void GameView::SetIsResizable(bool isResizable)
{
	m_impl->SetIsResizable(isResizable);
}

bool GameView::GetIsResizable()
{
	return m_impl->GetIsResizable();
}

GameView::GameView(IGameViewImpl* impl) : 
	m_impl(impl)
{

}

GameView::~GameView()
{

}