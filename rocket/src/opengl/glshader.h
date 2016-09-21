#pragma once
#ifndef ROCKET_INCLUDED_GLSHADER
#define ROCKET_INCLUDED_GLSHADER

#include "../renderer.h"
#include "../shader.h"
#include "rocket_opengl.h"

namespace Rocket
{
	namespace OpenGL
	{
		class GLShader : public Shader
		{
		public:
			GLShader();
			bool Create(const ShaderSource& source);

			~GLShader();

		private:

			GLuint CreateSubShader(GLenum type, size_t size, const void* data);

			GLuint m_program;
			GLuint m_frag;
			GLuint m_vert;
		};
	}
}

#endif