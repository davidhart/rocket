#pragma once
#ifndef ROCKET_INCLUDED_GAMEVIEW
#define ROCKET_INCLUDED_GAMEVIEW

#include "vectormath.h"

namespace Rocket
{
	class Renderer;

	class IGameViewSizeObserver
	{
	public:
		virtual void GameViewResized(const ivec2& size) = 0;
	};

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

		virtual void AddSizeObserver(IGameViewSizeObserver* observer) = 0;
		virtual void RemoveSizeObserver(IGameViewSizeObserver* observer) = 0;
	};

}

#endif