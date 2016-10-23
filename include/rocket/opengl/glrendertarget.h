#pragma once
#ifndef ROCKET_GLRENDERTRAGET_INCLUDED
#define ROCKET_GLRENDERTARGET_INCLUDED

#include "rendertarget.h"
#include "rocket_opengl.h"

#include <vector>

namespace Rocket
{
	namespace OpenGL
	{
		class GLTexture2D;

		class BaseGLRenderTarget : public RenderTarget
		{
			virtual GLuint GetNativeHandle() = 0;
		};

		class GLPrimaryRenderTarget : public BaseGLRenderTarget
		{
		public:
			virtual Texture2D* GetColorAttachment(int index);
			virtual Texture2D* GetDepthAttachment();
			virtual ivec2 GetSize() const;

			GLuint GetNativeHandle();
			void SetSize(const ivec2& size);

		private:
			ivec2 m_size;
		};

		class GLRenderTarget : public BaseGLRenderTarget
		{
		public:
			GLRenderTarget();
			~GLRenderTarget();

			bool Create(const RenderTargetDef& targetDef);

			virtual Texture2D* GetColorAttachment(int index);
			virtual Texture2D* GetDepthAttachment();
			virtual ivec2 GetSize() const;

			GLuint GetNativeHandle();

		private:
			GLuint m_framebuffer;
			ivec2 m_size;
			std::vector<GLTexture2D*> m_framebufferAttachements;
			GLTexture2D* m_depthAttachment;
		};
	}
}

#endif