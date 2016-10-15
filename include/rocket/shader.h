#pragma once
#ifndef ROCKET_INCLUDED_SHADER
#define ROCKET_INCLUDED_SHADER

#include "vectormath.h"

namespace Rocket
{
	struct ShaderDef
	{
		const void* vert;
		unsigned vertSize;

		const void* frag;
		unsigned fragSize;
	};

	class Texture1D;
    class Texture2D;
    class Texture3D;

	class ShaderParameters
	{
	public:
		virtual ~ShaderParameters();

		virtual void SetFloat(const char* name, float value) = 0;
		virtual void SetVec2(const char* name, const vec2& value) = 0;
		virtual void SetVec3(const char* name, const vec3& value) = 0;
		virtual void SetVec4(const char* name, const vec4& value) = 0;
		
		virtual void SetMat4(const char* name, const mat4& value) = 0;

		virtual void SetInt(const char* name, int value) = 0;
		virtual void SetIVec2(const char* name, const ivec2& value) = 0;
		virtual void SetIVec3(const char* name, const ivec3& value) = 0;
		virtual void SetIVec4(const char* name, const ivec4& value) = 0;
		
		virtual void SetTexture1D(const char* name, Texture1D* texture) = 0;
		virtual void SetTexture2D(const char* name, Texture2D* texture) = 0;
		virtual void SetTexture3D(const char* name, Texture3D* texture) = 0;
	};

	class Shader
	{
	protected:
		Shader();

	public:
		virtual ~Shader();
		virtual ShaderParameters* CreateParameters() = 0;
		virtual void ReleaseParameters(ShaderParameters* parameters) = 0;

	private:
		Shader(const Shader&);
	};
}

#endif
