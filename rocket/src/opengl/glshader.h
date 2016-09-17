#ifndef ROCKET_GLSHADER_H
#define ROCKET_GLSHADER_H

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