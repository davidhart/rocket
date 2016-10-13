#pragma once
#ifndef ROCKET_INCLUDED_RENDERER
#define ROCKET_INCLUDED_RENDERER

namespace Rocket
{
	class Buffer;
	class Shader;
	struct ShaderDef;
    
	class Texture1D;
    class Texture2D;
    class Texture3D;
    struct TextureDef1D;
    struct TextureDef2D;
    struct TextureDef3D;

	class DrawBinding;
	struct DrawBindingDef;

	class Material;

	class Renderer
	{
	public:
		virtual ~Renderer();

		virtual Buffer* CreateBuffer(unsigned size, void* data) = 0;
		virtual void ReleaseBuffer(Buffer* buffer) = 0;

		virtual Shader* CreateShader(const ShaderDef& shaderSource) = 0;
		virtual void ReleaseShader(Shader* shader) = 0;

        virtual Texture1D* CreateTexture(const TextureDef1D& textureData) = 0;
        virtual void ReleaseTexture(Texture1D* texture) = 0;
        
		virtual Texture2D* CreateTexture(const TextureDef2D& textureData) = 0;
        virtual void ReleaseTexture(Texture2D* texture) = 0;
        
        virtual Texture3D* CreateTexture(const TextureDef3D& textureData) = 0;
		virtual void ReleaseTexture(Texture3D* texture) = 0;

		virtual DrawBinding* CreateDrawBinding(const DrawBindingDef& drawBindingDef) = 0;
		virtual void ReleaseDrawBinding(DrawBinding* drawBinding) = 0;

		virtual void RenderTemp(DrawBinding* binding, Material* material) = 0;

		virtual void Present() = 0;
	};
}

#endif
