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

			virtual Buffer* CreateBuffer(size_t size, void* data);
			virtual void ReleaseBuffer(Buffer* buffer);

			virtual Shader* CreateShader(const ShaderDef& shaderSource);
			virtual void ReleaseShader(Shader* shader);

			virtual Texture* CreateTexture(const TextureDef& textureData);
			virtual void ReleaseTexture(Texture* texture);

			virtual DrawBinding* CreateDrawBinding(const DrawBindingDef& drawBindingDef);
			virtual void ReleaseDrawBinding(DrawBinding* drawBinding);

			virtual void Present();

		private:
			HWND m_hwnd;

			HDC m_hdc;
			HGLRC m_hglrc;
		};
	}
}

#endif