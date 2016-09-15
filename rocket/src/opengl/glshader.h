#ifndef ROCKET_GLSHADER_H
#define ROCKET_GLSHADER_H

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
			bool Create(size_t size, void* data);

			~GLShader();

		private:
			GLuint m_program;
			GLuint m_frag;
			GLuint m_vert;
		};
	}
}

#endif