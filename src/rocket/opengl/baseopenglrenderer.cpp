#include "opengl/baseopenglrenderer.h"
#include "opengl/glbuffer.h"
#include "opengl/glshader.h"
#include "opengl/gltexture.h"
#include "opengl/gldrawbinding.h"
#include "opengl/glrenderqueue.h"
#include "opengl/glrendertarget.h"

#include <cassert>

using namespace Rocket;
using namespace Rocket::OpenGL;

BaseOpenGLRenderer::BaseOpenGLRenderer()
{
}

bool BaseOpenGLRenderer::Create()
{
	return CreateContext();
}

RenderTarget* BaseOpenGLRenderer::GetPrimaryRenderTarget()
{
	return &m_primaryTarget;
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
	ActivateContext();

    delete buffer;
}

Shader* BaseOpenGLRenderer::CreateShader(const ShaderDef& def)
{
    ActivateContext();
    
    GLShader* shader = new GLShader();
    
    if (shader->Create(def) == false)
    {
		// Should never happen, failed to create error shader!
        delete shader;
		return nullptr;
    }
    
    return shader;
}

void BaseOpenGLRenderer::ReleaseShader(Shader* shader)
{
	ActivateContext();

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
	ActivateContext();

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
	ActivateContext();

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
	ActivateContext();

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
	ActivateContext();

    delete binding;
}

RenderTarget* BaseOpenGLRenderer::CreateRenderTarget(const RenderTargetDef& targetDef)
{
	GLRenderTarget* framebuffer = new GLRenderTarget();

	if (framebuffer->Create(targetDef) == false)
	{
		delete framebuffer;
		return nullptr;
	}

	return framebuffer;
}

void BaseOpenGLRenderer::ReleaseRenderTarget(RenderTarget* target)
{
	ActivateContext();

	delete target;
}

RenderQueue* BaseOpenGLRenderer::CreateRenderQueue(const char* name, int priority)
{
	//TODO: assert name is not already in use
	GLRenderQueue* queue = new GLRenderQueue(name, priority, GetPrimaryRenderTarget());

	auto it = m_renderQueues.begin();

	for (; it != m_renderQueues.end(); it++)
	{
		if (priority < (*it)->Priority())
		{
			m_renderQueues.insert(it, queue);
			return queue;
		}
	}

	m_renderQueues.push_back(queue);
	return queue;
}

RenderQueue* BaseOpenGLRenderer::GetRenderQueue(const char* name)
{
	for (size_t i = 0; i < m_renderQueues.size(); ++i)
	{
		if (strcmp(m_renderQueues[i]->Name(), name) == 0)
		{
			return m_renderQueues[i];
		}
	}

	return nullptr;
}

void BaseOpenGLRenderer::ReleaseRenderQueue(const char* name)
{
	GLRenderQueue* queue = nullptr;
	for (size_t i = 0; i < m_renderQueues.size(); ++i)
	{
		if (strcmp(m_renderQueues[i]->Name(), name) == 0)
		{
			queue = m_renderQueues[i];
			m_renderQueues.erase(m_renderQueues.begin() + i);
		}
	}

	assert(queue);
	delete queue;
}

void BaseOpenGLRenderer::ReleaseRenderQueue(RenderQueue* renderQueue)
{
	ReleaseRenderQueue(renderQueue->Name());
}

void BaseOpenGLRenderer::Present()
{
    ActivateContext();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	for (size_t i = 0; i < m_renderQueues.size(); ++i)
		m_renderQueues[i]->FlushQueue();
    
	glFlush();
    SwapBuffers();

    // Damn, map needs this
    //DeactivateContext();
}

void BaseOpenGLRenderer::GameViewResized(const ivec2& size)
{
	m_primaryTarget.SetSize(size);
}
