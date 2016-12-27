#pragma once
#ifndef ROCKET_INCLUDED_GLSHADER
#define ROCKET_INCLUDED_GLSHADER

#include "shader.h"
#include "rocket_opengl.h"

#include <vector>

namespace Rocket
{
	namespace OpenGL
	{
        class GLShaderGlobals;
        
		class GLShader : public Shader
		{
		public:
            struct Uniform
            {
                char* name;
                GLint location;
                int globalID;
            };
            
			GLShader();
			virtual ~GLShader();
			bool Create(const ShaderDef& source, GLShaderGlobals& globals);
            
			GLuint GetNativeHandle();
            
            const Uniform* Uniforms() const;
            size_t NumUniforms() const;
            
		private:

			bool CreateInternal(const ShaderDef& source, GLShaderGlobals& globals);
			GLuint CreateSubShader(GLenum type, unsigned size, const void* data);

			GLuint m_program;
            GLuint m_vert;
			GLuint m_frag;
            
            std::vector<Uniform> m_parameters;
		};
	}
}

#endif
