#pragma once

#ifndef ROCKET_INCLUDED_IGAMEVIEWIMPL
#define ROCKET_INCLUDED_IGAMEVIEWIMPL

namespace Rocket
{
	class Renderer;

	class IGameViewImpl
	{
	public:
		virtual ~IGameViewImpl() { };
		virtual bool Create() = 0;

		virtual Renderer* CreateRenderer() = 0;
		virtual void ReleaseRenderer(Renderer* renderer) = 0;

		virtual void SetTitle(const char* title) = 0;
		virtual void FlushEvents() = 0;
		virtual bool IsClosed() = 0;

		virtual void SetIsResizable(bool isResizable) = 0;
		virtual bool GetIsResizable() = 0;
	};

}

#endif