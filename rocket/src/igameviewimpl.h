#pragma once

#ifndef ROCKET_INCLUDED_IGAMEVIEWIMPL
#define ROCKET_INCLUDED_IGAMEVIEWIMPL

namespace Rocket
{

	class IGameViewImpl
	{
	public:
		virtual ~IGameViewImpl() { };
		virtual bool Create() = 0;
		virtual void SetTitle(const char* title) = 0;
		virtual void FlushEvents() = 0;
		virtual bool IsClosed() = 0;
	};

}

#endif