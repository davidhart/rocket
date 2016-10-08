#pragma once
#ifndef ROCKET_INCLUDED_GLSHADER
#define ROCKET_INCLUDED_GLSHADER

#include "shader.h"
#include "renderer.h"
#include "rocket_opengl.h"

#include <map>
#include <string>

namespace Rocket
{
	namespace OpenGL
	{
		class GLShader : public Shader
		{
		public:
			GLShader();
			virtual ~GLShader();
			bool Create(const ShaderDef& source);

			virtual ShaderParameters* CreateParameters();
			virtual void ReleaseParameters(ShaderParameters* parameters);

			GLuint GetNativeHandle();

		private:

			GLuint CreateSubShader(GLenum type, unsigned size, const void* data);

			GLuint m_program;
            GLuint m_vert;
			GLuint m_frag;
		};

		union ParameterValue
		{
			float f;
			vec2 v2;
			vec3 v3;
			vec4 v4;
		};

		struct ParameterData;
		typedef void(*SetFunc)(const ParameterData& parameter);

		struct ParameterData
		{
			GLint location;
			ParameterValue value;
			SetFunc setter;

			ParameterData();
		};

		class GLShaderParameters : public ShaderParameters
		{
		public:
			GLShaderParameters(GLuint program);

			typedef std::map<std::string, ParameterData> ParameterCollection;

			virtual void SetFloat(const char* name, float val);
			virtual void SetVec2(const char* name, const vec2& val);
			virtual void SetVec3(const char* name, const vec3& val);
			virtual void SetVec4(const char* name, const vec4& val);

			void MakeCurrent();

		private:
			
			GLuint m_program;
			ParameterCollection m_parameters;
		};
	}
}

#endif
