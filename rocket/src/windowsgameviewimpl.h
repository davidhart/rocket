#pragma once

#ifndef ROCKET_INCLUDED_WINDOWSGAMEVIEWIMPL
#define ROCKET_INCLUDED_WINDOWSGAMEVIEWIMPL

#include "igameviewimpl.h"

#include <Windows.h>

namespace Rocket
{
	namespace Windows
	{
		class WindowsGameViewImpl : public IGameViewImpl
		{
		public:
			WindowsGameViewImpl();
			virtual ~WindowsGameViewImpl();
			virtual bool Create();
			virtual void SetTitle(const char* title);
			virtual void FlushEvents();
			virtual bool IsClosed();
			LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

		private:

			bool m_isClassRegistered;
			HWND m_hwnd;
			bool m_isWindowClosed;
		};
	}
}

#endif