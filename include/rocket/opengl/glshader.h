#pragma once
#ifndef ROCKET_INCLUDED_GLSHADER
#define ROCKET_INCLUDED_GLSHADER

#include "shader.h"
#include "renderer.h"
#include "texture.h"
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
			int GetParameterLocation(const char* name);

		private:

			GLuint CreateSubShader(GLenum type, unsigned size, const void* data);

			GLuint m_program;
            GLuint m_vert;
			GLuint m_frag;

			std::map<std::string, int> m_shaderParameterLocations;
		};

		union ParameterValue
		{
			float f;
			vec2 v2;
			vec3 v3;
			vec4 v4;

			int i;
			ivec2 iv2;
			ivec3 iv3;
			ivec4 iv4;

			Texture* texture;

			ParameterValue();
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

		struct TextureSampler
		{
			GLint location;
			Texture* texture;
			TextureType type;
		};

		class GLShaderParameters : public ShaderParameters
		{
		public:
			GLShaderParameters(GLShader* shader);

			typedef std::map<std::string, ParameterData> ParameterCollection;
			typedef std::map<std::string, TextureSampler> TextureCollection;

			virtual void SetFloat(const char* name, float value);
			virtual void SetVec2(const char* name, const vec2& value);
			virtual void SetVec3(const char* name, const vec3& value);
			virtual void SetVec4(const char* name, const vec4& value);

			virtual void SetInt(const char* name, int value);
			virtual void SetIVec2(const char* name, const ivec2& value);
			virtual void SetIVec3(const char* name, const ivec3& value);
			virtual void SetIVec4(const char* name, const ivec4& value);

			virtual void SetTexture1D(const char* name, Texture* texture);
			virtual void SetTexture2D(const char* name, Texture* texture);
			virtual void SetTexture3D(const char* name, Texture* texture);

			void MakeCurrent();

		private:

			void Set(const char* name, const ParameterValue& value, SetFunc func);
			
			GLShader* m_shader;
			ParameterCollection m_parameters;
			TextureCollection m_textures;
		};
	}
}

#endif
