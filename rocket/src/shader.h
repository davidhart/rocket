#ifndef ROCKET_SHADER_H
#define ROCKET_SHADER_H

namespace Rocket
{
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