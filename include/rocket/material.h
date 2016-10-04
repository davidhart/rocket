#pragma once
#ifndef ROCKET_MATERIAL_INCLUDED
#define ROCKET_MATERIAL_INCLUDED

namespace Rocket
{
	class Shader;

	class Material
	{
	public:
		Material(Shader* shader);
		Material(const Material& material);
		~Material();

		Shader* GetShader();

	private:
		Shader* m_shader;
	};
}

#endif