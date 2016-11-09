#pragma once

#ifndef ROCKET_INCLUDED_WINDOWSGAMEVIEWIMPL
#define ROCKET_INCLUDED_WINDOWSGAMEVIEWIMPL

#if defined(_WIN32)

#include "vectormath.h"
#include "implementation/basegameview.h"
#include <Windows.h>

namespace Rocket
{
	namespace Windows
	{
        class WindowsKeyboard;

		class WindowsGameView : public Implementation::BaseGameView 
		{
		public:
			WindowsGameView();
			virtual ~WindowsGameView();
			bool Create();

			virtual Renderer* CreateRenderer();
			virtual void ReleaseRenderer(Renderer* renderer);

			virtual void SetTitle(const char* title);
			virtual void Update(float delta);
			virtual bool IsClosed();
            
			virtual void SetIsResizable(bool isResizable);
			virtual bool GetIsResizable();
			virtual ivec2 GetSize() const;

            virtual int TranslateKeyCodeToNative(Input::KeyCode code);

			LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
            
		private:

			HWND m_hwnd;
			bool m_isClassRegistered;
			bool m_isWindowClosed;
			bool m_isResizable;
			ivec2 m_size;

            std::vector<WindowsKeyboard*> m_keyboardControls;
		};
	}
}

#endif

#endif
