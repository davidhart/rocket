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
        virtual ~Material();

		virtual Shader* GetShader() = 0;
		virtual ShaderParameters* GetParameters() = 0;
	};
}

#endif
