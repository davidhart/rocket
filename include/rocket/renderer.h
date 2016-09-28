#pragma once
#ifndef ROCKET_INCLUDED_RENDERER
#define ROCKET_INCLUDED_RENDERER

namespace Rocket
{
	class Buffer;
	class Shader;
	struct ShaderDef;
	class Texture;
	struct TextureDef;

	class DrawBinding;
	struct DrawBindingDef;

	class Renderer
	{
	public:
		virtual ~Renderer();

		virtual Buffer* CreateBuffer(size_t size, void* data) = 0;
		virtual void ReleaseBuffer(Buffer* buffer) = 0;

		virtual Shader* CreateShader(const ShaderDef& shaderSource) = 0;
		virtual void ReleaseShader(Shader* shader) = 0;

		virtual Texture* CreateTexture(const TextureDef& textureData) = 0;
		virtual void ReleaseTexture(Texture* texture) = 0;

		virtual DrawBinding* CreateDrawBinding(const DrawBindingDef& drawBindingDef) = 0;
		virtual void ReleaseDrawBinding(DrawBinding* drawBinding) = 0;

		virtual void RenderTemp(DrawBinding* binding, Shader* shader) = 0;

		virtual void Present() = 0;
	};
}

#endif