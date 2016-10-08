#pragma once
#ifndef ROCKET_MATERIAL_INCLUDED
#define ROCKET_MATERIAL_INCLUDED

namespace Rocket
{
	class Shader;
	class ShaderParameters;

	class Material
	{
	public:
		Material(Shader* shader);
		Material(const Material& material);
		~Material();

		Shader* GetShader();
		ShaderParameters* GetParameters();

	private:
		Shader* m_shader;
		ShaderParameters* m_parameters;
	};
}

#endif