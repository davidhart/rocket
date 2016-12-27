#pragma once
#ifndef ROCKET_BASEOPENGLRENDERER_DEFINED
#define ROCKET_BASEOPENGLRENDERER_DEFINED

#include "renderer.h"
#include "gameview.h"
#include "glrendertarget.h"
#include "glshaderglobals.h"
#include <vector>

namespace Rocket
{
	namespace OpenGL
	{
		class GLRenderQueue;
	}

    class BaseOpenGLRenderer : public Renderer, public IGameViewSizeObserver
    {
    protected:
        BaseOpenGLRenderer();
        
        virtual bool CreateContext() = 0;
        virtual void SwapBuffers() = 0;
        
    public:
        bool Create();
        
		virtual RenderTarget* GetPrimaryRenderTarget();

        virtual Buffer* CreateBuffer(unsigned size, void* data);
        virtual void ReleaseBuffer(Buffer* buffer);
        
        virtual Shader* CreateShader(const ShaderDef& shaderSource);
        virtual void ReleaseShader(Shader* shader);
        
        virtual Material* CreateMaterial(Shader* shader);
        virtual void ReleaseMaterial(Material* material);
        
        virtual Texture1D* CreateTexture(const TextureDef1D& textureData);
        virtual void ReleaseTexture(Texture1D* texture);
        
        virtual Texture2D* CreateTexture(const TextureDef2D& textureData);
        virtual void ReleaseTexture(Texture2D* texture);
        
        virtual Texture3D* CreateTexture(const TextureDef3D& textureData);
        virtual void ReleaseTexture(Texture3D* texture);
        
        virtual DrawBinding* CreateDrawBinding(const DrawBindingDef& drawBindingDef);
        virtual void ReleaseDrawBinding(DrawBinding* drawBinding);

		virtual RenderTarget* CreateRenderTarget(const RenderTargetDef& targetDef);
		virtual void ReleaseRenderTarget(RenderTarget* target);

		virtual RenderQueue* CreateRenderQueue(const char* name, int priority);
		virtual RenderQueue* GetRenderQueue(const char* name);
		virtual void ReleaseRenderQueue(const char* name);
		virtual void ReleaseRenderQueue(RenderQueue* renderQueue);
        
        virtual int GetShaderPropertyID(const char* name);
        virtual void SetShaderGlobal(const char* name, float value);
        virtual void SetShaderGlobal(const char* name, const vec2& value);
        virtual void SetShaderGlobal(const char* name, const vec3& value);
        virtual void SetShaderGlobal(const char* name, const vec4& value);
        virtual void SetShaderGlobal(const char* name, const mat4& value);
        virtual void SetShaderGlobal(const char* name, int value);
        virtual void SetShaderGlobal(const char* name, const ivec2& value);
        virtual void SetShaderGlobal(const char* name, const ivec3& value);
        virtual void SetShaderGlobal(const char* name, const ivec4& value);
        virtual void SetShaderGlobal(const char* name, Texture1D* texture);
        virtual void SetShaderGlobal(const char* name, Texture2D* texture);
        virtual void SetShaderGlobal(const char* name, Texture3D* texture);
        
        virtual void SetShaderGlobal(int propertyID, float value);
        virtual void SetShaderGlobal(int propertyID, const vec2& value);
        virtual void SetShaderGlobal(int propertyID, const vec3& value);
        virtual void SetShaderGlobal(int propertyID, const vec4& value);
        virtual void SetShaderGlobal(int propertyID, const mat4& value);
        virtual void SetShaderGlobal(int propertyID, int value);
        virtual void SetShaderGlobal(int propertyID, const ivec2& value);
        virtual void SetShaderGlobal(int propertyID, const ivec3& value);
        virtual void SetShaderGlobal(int propertyID, const ivec4& value);
        virtual void SetShaderGlobal(int propertyID, Texture1D* texture);
        virtual void SetShaderGlobal(int propertyID, Texture2D* texture);
        virtual void SetShaderGlobal(int propertyID, Texture3D* texture);
        
        virtual void Present();
        
		virtual void GameViewResized(const ivec2& size);

    private:
		std::vector<OpenGL::GLRenderQueue*> m_renderQueues;
		OpenGL::GLPrimaryRenderTarget m_primaryTarget;
        OpenGL::GLShaderGlobals m_globals;
    };
}

#endif
