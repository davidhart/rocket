#pragma once

#ifndef ROCKET_INCLUDED_RENDERER
#define ROCKET_INCLUDED_RENDERER

namespace Rocket
{
	class VertexBuffer;

	class Renderer
	{
	public:
		virtual ~Renderer();

		virtual VertexBuffer* CreateVertexBuffer(size_t size, void* data) = 0;
		virtual void ReleaseVertexBuffer(VertexBuffer* buffer) = 0;

		virtual void Present() = 0;
	};
}

#endif