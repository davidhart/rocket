#pragma once

#ifndef ROCKET_INCLUDED_GAMEVIEW
#define ROCKET_INCLUDED_GAMEVIEW

namespace Rocket
{

	class IGameViewImpl;

	class GameView
	{
	public:
		static GameView* Create(const char* title);
		static void Release(GameView* view);

		void SetTitle(const char* title);

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