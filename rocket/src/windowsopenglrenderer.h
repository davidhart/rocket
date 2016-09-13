#pragma once

#ifndef ROCKET_INCLUDED_WINDOWSOPENGLRENDERER
#define ROCKET_INCLUDED_WINDOWSOPENGLRENDERER

#include "renderer.h"

#include <Windows.h>

namespace Rocket
{
	namespace Windows
	{
		class WindowsOpenGLRenderer : public Renderer
		{
		public:
			WindowsOpenGLRenderer(HWND hwnd);
			virtual ~WindowsOpenGLRenderer();
			bool Create();

			virtual VertexBuffer* CreateVertexBuffer(size_t size, void* data);
			virtual void ReleaseVertexBuffer(VertexBuffer* buffer);

			virtual void Present();

		private:
			HWND m_hwnd;

			HDC m_hdc;
			HGLRC m_hglrc;
		};
	}
}

#endif