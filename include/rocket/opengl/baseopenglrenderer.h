#pragma once
#ifndef ROCKET_BASEOPENGLRENDERER_DEFINED
#define ROCKET_BASEOPENGLRENDERER_DEFINED

#include "renderer.h"
#include <queue>

namespace Rocket
{
    class BaseOpenGLRenderer : public Renderer
    {
    protected:
        BaseOpenGLRenderer();
        
        virtual bool CreateContext() = 0;
        virtual void ActivateContext() = 0;
        virtual void DeactivateContext() = 0;
        virtual void SwapBuffers() = 0;
        
    public:
        bool Create();
        
        virtual Buffer* CreateBuffer(unsigned size, void* data);
        virtual void ReleaseBuffer(Buffer* buffer);
        
        virtual Shader* CreateShader(const ShaderDef& shaderSource);
        virtual void ReleaseShader(Shader* shader);
        
        virtual Texture1D* CreateTexture(const TextureDef1D& textureData);
        virtual void ReleaseTexture(Texture1D* texture);
        
        virtual Texture2D* CreateTexture(const TextureDef2D& textureData);
        virtual void ReleaseTexture(Texture2D* texture);
        
        virtual Texture3D* CreateTexture(const TextureDef3D& textureData);
        virtual void ReleaseTexture(Texture3D* texture);
        
        virtual DrawBinding* CreateDrawBinding(const DrawBindingDef& drawBindingDef);
        virtual void ReleaseDrawBinding(DrawBinding* drawBinding);
        
        virtual void RenderTemp(DrawBinding* drawBinding, Material* shader);
        
        virtual void Present();
        
    private:
        
        struct TempDraw
        {
            DrawBinding* binding;
            Material* material;
        };
        
        std::queue<TempDraw> m_tempDrawQueue;
    };
}

#endif
