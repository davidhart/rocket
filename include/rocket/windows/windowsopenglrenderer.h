#pragma once

#ifndef ROCKET_INCLUDED_WINDOWSOPENGLRENDERER
#define ROCKET_INCLUDED_WINDOWSOPENGLRENDERER

#ifdef _WIN32

#include "opengl/baseopenglrenderer.h"

#include <Windows.h>

namespace Rocket
{
	namespace Windows
    {
		class WindowsOpenGLRenderer : public BaseOpenGLRenderer
		{
		public:
			WindowsOpenGLRenderer(HWND hwnd);
			virtual ~WindowsOpenGLRenderer();
			virtual bool CreateContext();
            virtual void ActivateContext();
            virtual void DeactivateContext();
            virtual void SwapBuffers();

		private:
			HWND m_hwnd;

			HDC m_hdc;
			HGLRC m_hglrc;
		};
	}
}

#endif

#endif
