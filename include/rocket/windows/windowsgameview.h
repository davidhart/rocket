#pragma once

#ifndef ROCKET_INCLUDED_WINDOWSGAMEVIEWIMPL
#define ROCKET_INCLUDED_WINDOWSGAMEVIEWIMPL

#if defined(_WIN32)

#include "vectormath.h"
#include "implementation/basegameview.h"
#include <Windows.h>
#include <map>
#include <functional>

namespace Rocket
{
    namespace Implementation
    {
        class Button;
        
    }

	namespace Windows
	{
        class WindowsRuntimeControls
        {
        public:
            WindowsRuntimeControls(Implementation::RuntimeControls* controls, Implementation::ControlScheme* scheme);
            const Implementation::RuntimeControls* RuntimeControls() const;

            static void ButtonDown(Implementation::Button* button);
            static void ButtonUp(Implementation::Button* button);

            void KeyDown(int nativeCode);
            void KeyUp(int nativeCode);

        private:
            const Implementation::RuntimeControls* m_controls;
            std::map<int, std::function<void()>> m_keyDown;
            std::map<int, std::function<void()>> m_keyUp;
        };

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

            virtual void RuntimeControlsActivated(Implementation::RuntimeControls* controls, Implementation::ControlScheme* scheme);
            virtual void RuntimeControlsDeactivated(Implementation::RuntimeControls* controls);

			LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
            
		private:

			HWND m_hwnd;
			bool m_isClassRegistered;
			bool m_isWindowClosed;
			bool m_isResizable;
			ivec2 m_size;

            std::vector<WindowsRuntimeControls*> m_controls;
		};
	}
}

#endif

#endif
