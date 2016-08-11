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

			virtual Renderer* CreateRenderer();
			virtual void ReleaseRenderer(Renderer* renderer);

			virtual void SetTitle(const char* title);
			virtual void FlushEvents();
			virtual bool IsClosed();
			virtual void SetIsResizable(bool isResizable);
			virtual bool GetIsResizable();

			LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

		private:

			HWND m_hwnd;
			bool m_isClassRegistered;
			bool m_isWindowClosed;
			bool m_isResizable;
		};
	}
}

#endif