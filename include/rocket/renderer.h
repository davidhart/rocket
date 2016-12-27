#pragma once
#ifndef ROCKET_INCLUDED_RENDERER
#define ROCKET_INCLUDED_RENDERER

#include "vectormath.h"

namespace Rocket
{
	class Buffer;
	class Shader;
    class Material;
	struct ShaderDef;
    
	class Texture1D;
    class Texture2D;
    class Texture3D;
    struct TextureDef1D;
    struct TextureDef2D;
    struct TextureDef3D;

	class DrawBinding;
	struct DrawBindingDef;

	class RenderTarget;
	struct RenderTargetDef;

	class RenderQueue;

	class Renderer
	{
	public:
		virtual ~Renderer();

		virtual RenderTarget* GetPrimaryRenderTarget() = 0;

		virtual Buffer* CreateBuffer(unsigned size, void* data) = 0;
		virtual void ReleaseBuffer(Buffer* buffer) = 0;

		virtual Shader* CreateShader(const ShaderDef& shaderSource) = 0;
		virtual void ReleaseShader(Shader* shader) = 0;
        
        virtual Material* CreateMaterial(Shader* shader) = 0;
        virtual void ReleaseMaterial(Material* material) = 0;

        virtual Texture1D* CreateTexture(const TextureDef1D& textureData) = 0;
        virtual void ReleaseTexture(Texture1D* texture) = 0;
        
		virtual Texture2D* CreateTexture(const TextureDef2D& textureData) = 0;
        virtual void ReleaseTexture(Texture2D* texture) = 0;
        
        virtual Texture3D* CreateTexture(const TextureDef3D& textureData) = 0;
		virtual void ReleaseTexture(Texture3D* texture) = 0;

		virtual DrawBinding* CreateDrawBinding(const DrawBindingDef& drawBindingDef) = 0;
		virtual void ReleaseDrawBinding(DrawBinding* drawBinding) = 0;

		virtual RenderTarget* CreateRenderTarget(const RenderTargetDef& targetDef) = 0;
		virtual void ReleaseRenderTarget(RenderTarget* target) = 0;

		virtual RenderQueue* CreateRenderQueue(const char* name, int priority) = 0;
		virtual RenderQueue* GetRenderQueue(const char* name) = 0;
		virtual void ReleaseRenderQueue(const char* name) = 0;
		virtual void ReleaseRenderQueue(RenderQueue* renderQueue) = 0;
        
        virtual int GetShaderPropertyID(const char* name) = 0;
        virtual void SetGlobalFloat(const char* name, float value) = 0;
        virtual void SetGlobalVec2(const char* name, const vec2& value) = 0;
        virtual void SetGlobalVec3(const char* name, const vec3& value) = 0;
        virtual void SetGlobalVec4(const char* name, const vec4& value) = 0;
        virtual void SetGlobalMat4(const char* name, const mat4& value) = 0;
        virtual void SetGlobalInt(const char* name, int value) = 0;
        virtual void SetGlobalIVec2(const char* name, const ivec2& value) = 0;
        virtual void SetGlobalIVec3(const char* name, const ivec3& value) = 0;
        virtual void SetGlobalIVec4(const char* name, const ivec4& value) = 0;
        virtual void SetGlobalTexture1D(const char* name, Texture1D* texture) = 0;
        virtual void SetGlobalTexture2D(const char* name, Texture2D* texture) = 0;
        virtual void SetGlobalTexture3D(const char* name, Texture3D* texture) = 0;
        
        virtual void SetGlobalFloat(int propertyID, float value) = 0;
        virtual void SetGlobalVec2(int propertyID, const vec2& value) = 0;
        virtual void SetGlobalVec3(int propertyID, const vec3& value) = 0;
        virtual void SetGlobalVec4(int propertyID, const vec4& value) = 0;
        virtual void SetGlobalMat4(int propertyID, const mat4& value) = 0;
        virtual void SetGlobalInt(int propertyID, int value) = 0;
        virtual void SetGlobalIVec2(int propertyID, const ivec2& value) = 0;
        virtual void SetGlobalIVec3(int propertyID, const ivec3& value) = 0;
        virtual void SetGlobalIVec4(int propertyID, const ivec4& value) = 0;
        virtual void SetGlobalTexture1D(int propertyID, Texture1D* texture) = 0;
        virtual void SetGlobalTexture2D(int propertyID, Texture2D* texture) = 0;
        virtual void SetGlobalTexture3D(int propertyID, Texture3D* texture) = 0;

        
		virtual void Present() = 0;
	};
}

#endif
