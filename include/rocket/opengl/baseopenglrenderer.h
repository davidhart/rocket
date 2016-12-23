#pragma once
#ifndef ROCKET_BASEOPENGLRENDERER_DEFINED
#define ROCKET_BASEOPENGLRENDERER_DEFINED

#include "renderer.h"
#include "gameview.h"
#include "glrendertarget.h"
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
        
		// Renderer implementation
		virtual RenderTarget* GetPrimaryRenderTarget();

        virtual Buffer* CreateBuffer(unsigned size, void* data);
        virtual void ReleaseBuffer(Buffer* buffer);
        
        virtual Shader* CreateShader(const ShaderDef& shaderSource);
        virtual void ReleaseShader(Shader* shader);
        
        virtual Material* CreateMaterial(Shader* shader);
        virtual Material* CreateMaterial(Material* material);
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
        
        virtual void Present();
        
		// IGameViewSizeObserver implementation
		virtual void GameViewResized(const ivec2& size);

    private:
		std::vector<OpenGL::GLRenderQueue*> m_renderQueues;
		OpenGL::GLPrimaryRenderTarget m_primaryTarget;
    };
}

#endif
