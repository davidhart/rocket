#pragma once

#ifndef ROCKET_INCLUDED_GAMEVIEW
#define ROCKET_INCLUDED_GAMEVIEW

namespace Rocket
{
	class Renderer;

	class GameView
	{
	public:
		
		static GameView* Create(const char* title);
		static void Release(GameView* view);
		virtual ~GameView();

		virtual Renderer* CreateRenderer() = 0;
		virtual void ReleaseRenderer(Renderer* renderer) = 0;

		virtual void SetTitle(const char* title) = 0;

		virtual void SetIsResizable(bool isResizable) = 0;
		virtual bool GetIsResizable() = 0;

		virtual void FlushEvents() = 0;
		virtual bool IsClosed() = 0;
	};

}

#endif