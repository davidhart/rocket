#pragma once
#ifndef ROCKET_INCLUDED_SHADER
#define ROCKET_INCLUDED_SHADER

namespace Rocket
{
	struct ShaderSource
	{
		void* vert;
		size_t vertSize;

		void* frag;
		size_t fragSize;
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