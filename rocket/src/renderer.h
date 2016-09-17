#pragma once

#ifndef ROCKET_INCLUDED_RENDERER
#define ROCKET_INCLUDED_RENDERER

namespace Rocket
{
	class VertexBuffer;
	class Shader;
	struct ShaderSource;

	class Renderer
	{
	public:
		virtual ~Renderer();

		virtual VertexBuffer* CreateVertexBuffer(size_t size, void* data) = 0;
		virtual void ReleaseVertexBuffer(VertexBuffer* buffer) = 0;

		virtual Shader* CreateShader(const ShaderSource& shaderSource) = 0;
		virtual void ReleaseShader(Shader* shader) = 0;

		virtual void Present() = 0;
	};
}

#endif