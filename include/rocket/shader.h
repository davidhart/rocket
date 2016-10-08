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

	class ShaderParameters
	{
	public:
		virtual ~ShaderParameters();

		virtual void SetFloat(const char* name, float value) = 0;
		virtual void SetVec2(const char* name, const vec2& value) = 0;
		virtual void SetVec3(const char* name, const vec3& value) = 0;
		virtual void SetVec4(const char* name, const vec4& value) = 0;
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
