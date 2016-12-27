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
    
	class Shader
	{
	protected:
		Shader();

	public:
		virtual ~Shader();

	private:
		Shader(const Shader&);
	};
}

#endif
