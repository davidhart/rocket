#include "opengl/baseopenglrenderer.h"
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

Texture1D* BaseOpenGLRenderer::CreateTexture(const TextureDef1D& def)
{
    ActivateContext();
    
    GLTexture1D* texture = new GLTexture1D();
    
    if (texture->Create(def) == false)
    {
        delete texture;
        return nullptr;
    }
    
    return texture;
}


void BaseOpenGLRenderer::ReleaseTexture(Texture1D* texture)
{
    delete texture;
}

Texture2D* BaseOpenGLRenderer::CreateTexture(const TextureDef2D& def)
{
    ActivateContext();
    
    GLTexture2D* texture = new GLTexture2D();
    
    if (texture->Create(def) == false)
    {
        delete texture;
        return nullptr;
    }
    
    return texture;
}

void BaseOpenGLRenderer::ReleaseTexture(Texture2D* texture)
{
    delete texture;
}

Texture3D* BaseOpenGLRenderer::CreateTexture(const TextureDef3D& def)
{
    ActivateContext();
    
    GLTexture3D* texture = new GLTexture3D();
    
    if (texture->Create(def) == false)
    {
        delete texture;
        return nullptr;
    }
    
    return texture;
}

void BaseOpenGLRenderer::ReleaseTexture(Texture3D* texture)
{
    delete texture;
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

		GLShaderParameters* parameters = (GLShaderParameters*)material->GetParameters();
		parameters->MakeCurrent();

        GLsizei numElements = ((GLDrawBinding*)draw.binding)->GetNumElements();
        glDrawArrays(GL_TRIANGLES, 0, numElements);
        
        m_tempDrawQueue.pop();
    }
    
	glFlush();
    SwapBuffers();
    DeactivateContext();
}

void BaseOpenGLRenderer::GameViewResized(const ivec2& vec)
{
	ActivateContext();
	glViewport(0, 0, vec.x, vec.y);
	DeactivateContext();
}
