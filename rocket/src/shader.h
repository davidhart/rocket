#ifndef ROCKET_SHADER_H
#define ROCKET_SHADER_H

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