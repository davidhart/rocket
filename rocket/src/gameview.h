#pragma once

#ifndef ROCKET_INCLUDED_GAMEVIEW
#define ROCKET_INCLUDED_GAMEVIEW

namespace Rocket
{
	class IGameViewImpl;
	class Renderer;

	class GameView
	{
	public:
		
		static GameView* Create(const char* title);
		static void Release(GameView* view);

		Renderer* CreateRenderer();
		void ReleaseRenderer(Renderer* renderer);

		void SetTitle(const char* title);

		void SetIsResizable(bool isResizable);
		bool GetIsResizable();

		void FlushEvents();
		bool IsClosed();

	private:
		GameView(IGameViewImpl* impl);
		GameView(const GameView& view);
		~GameView();

		IGameViewImpl* m_impl;
	};

}

#endif