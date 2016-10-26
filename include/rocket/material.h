#pragma once
#ifndef ROCKET_MATERIAL_INCLUDED
#define ROCKET_MATERIAL_INCLUDED

#include "api.h"

namespace Rocket
{
	class Shader;
	class ShaderParameters;

	class Material
	{
	public:
		ROCKET_API Material(Shader* shader);
		ROCKET_API Material(const Material& material);
		ROCKET_API ~Material();

		ROCKET_API Shader* GetShader();
		ROCKET_API ShaderParameters* GetParameters();

	private:
		Shader* m_shader;
		ShaderParameters* m_parameters;
	};
}

#endif