#pragma once
#ifndef ROCKET_GLFRAMEBUFFER_INCLUDED
#define ROCKET_GLFRAMEBUFFER_INCLUDED

#include "framebuffer.h"
#include "rocket_opengl.h"

#include <vector>

namespace Rocket
{
	namespace OpenGL
	{
		class GLTexture2D;

		class GLFramebuffer : public Framebuffer
		{
		public:
			GLFramebuffer();
			~GLFramebuffer();

			bool Create(const FramebufferDef& framebufferDef);

			virtual Texture2D* GetColorAttachment(int index);
			virtual Texture2D* GetDepthAttachment();
			virtual ivec2 GetSize();

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