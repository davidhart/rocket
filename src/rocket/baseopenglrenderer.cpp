#include "baseopenglrenderer.h"
#include "material.h"

#include "opengl/glbuffer.h"
#include "opengl/glshader.h"
#include "opengl/gltexture.h"
#include "opengl/gldrawbinding.h"

using namespace Rocket;
using namespace Rocket::OpenGL;

BaseOpenGLRenderer::BaseOpenGLRenderer()
{
}

bool BaseOpenGLRenderer::Create()
{
    return CreateContext();
}

Buffer* BaseOpenGLRenderer::CreateBuffer(unsigned size, void* data)
{
    ActivateContext();
    
    GLBuffer* buffer = new GLBuffer();
    
    if (buffer->Create(size, data) == false)
    {
        delete buffer;
        return nullptr;
    }
    
    return buffer;
}

void BaseOpenGLRenderer::ReleaseBuffer(Buffer* buffer)
{
    delete buffer;
}

Shader* BaseOpenGLRenderer::CreateShader(const ShaderDef& def)
{
    ActivateContext();
    
    GLShader* shader = new GLShader();
    
    if (shader->Create(def) == false)
    {
        delete shader;
        return nullptr;
    }
    
    return shader;
}

void BaseOpenGLRenderer::ReleaseShader(Shader* shader)
{
    delete shader;
}

Texture* BaseOpenGLRenderer::CreateTexture(const TextureDef& def)
{
    ActivateContext();
    
    GLTexture* texture = new GLTexture();
    
    if (texture->Create(def) == false)
    {
        delete texture;
        return nullptr;
    }
    
    return texture;
}

DrawBinding* BaseOpenGLRenderer::CreateDrawBinding(const DrawBindingDef& def)
{
    ActivateContext();
    
    GLDrawBinding* binding = new GLDrawBinding();
    
    if (binding->Create(def) == false)
    {
        delete binding;
        return nullptr;
    }
    
    return binding;
}

void BaseOpenGLRenderer::ReleaseDrawBinding(DrawBinding* binding)
{
    delete binding;
}

void BaseOpenGLRenderer::ReleaseTexture(Texture* texture)
{
    delete texture;
}

void BaseOpenGLRenderer::RenderTemp(DrawBinding* binding, Material* shader)
{
	TempDraw draw = {
		binding, shader
	};

    m_tempDrawQueue.push(draw);
}

void BaseOpenGLRenderer::Present()
{
    ActivateContext();
    
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    while (m_tempDrawQueue.empty() == false)
    {
        TempDraw draw = m_tempDrawQueue.front();
        
        GLuint vaohandle = ((GLDrawBinding*)draw.binding)->GetNativeHandle();
        glBindVertexArray(vaohandle);

		Material* material = draw.material;
        
        GLuint shaderhandle = ((GLShader*)material->GetShader())->GetNativeHandle();
        glUseProgram(shaderhandle);
        
        GLsizei numElements = ((GLDrawBinding*)draw.binding)->GetNumElements();
        glDrawArrays(GL_TRIANGLES, 0, numElements);
        
        m_tempDrawQueue.pop();
    }
    
    SwapBuffers();
    DeactivateContext();
}
