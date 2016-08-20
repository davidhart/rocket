#pragma once

#ifndef ROCKET_INCLUDED_RENDERER
#define ROCKET_INCLUDED_RENDERER

namespace Rocket
{
	class Renderer
	{
	public:
		virtual ~Renderer();

		virtual void Present() = 0;
	};
}

#endif