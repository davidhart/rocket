#include "opengl/baseopenglrenderer.h"
#include "opengl/glbuffer.h"
#include "opengl/glshader.h"
#include "opengl/gltexture.h"
#include "opengl/gldrawbinding.h"
#include "opengl/glrenderqueue.h"
#include "opengl/glrendertarget.h"
#include "opengl/glmaterial.h"

#include <cassert>

using namespace Rocket;
using namespace Rocket::OpenGL;

static bool GLOBAL_OPENGL_CONTEXT_IS_INITIALISED = false;

BaseOpenGLRenderer::BaseOpenGLRenderer()
{
}

bool BaseOpenGLRenderer::Create()
{
    if (GLOBAL_OPENGL_CONTEXT_IS_INITIALISED)
    {
        assert(false); // OpenGL renderer implementation does not support multiple simultaneous instances
        return false;
    }

	GLOBAL_OPENGL_CONTEXT_IS_INITIALISED = CreateContext();
    return GLOBAL_OPENGL_CONTEXT_IS_INITIALISED;
}

RenderTarget* BaseOpenGLRenderer::GetPrimaryRenderTarget()
{
	return &m_primaryTarget;
}

Buffer* BaseOpenGLRenderer::CreateBuffer(unsigned size, void* data)
{   
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
    GLShader* shader = new GLShader();
    
    if (shader->Create(def, m_globals) == false)
    {
		// Should never happen, failed to create error shader!
        delete shader;
		return nullptr;
    }
    
    return shader;
}

void BaseOpenGLRenderer::ReleaseShader(Shader* shader)
{
    delete shader;
}

Material* BaseOpenGLRenderer::CreateMaterial(Shader* shader)
{
    return new GLMaterial((GLShader*)shader);
}

void BaseOpenGLRenderer::ReleaseMaterial(Material* material)
{
    delete material;
}

Texture1D* BaseOpenGLRenderer::CreateTexture(const TextureDef1D& def)
{   
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
	delete target;
}

RenderQueue* BaseOpenGLRenderer::CreateRenderQueue(const char* name, int priority)
{
	//TODO: assert name is not already in use
	GLRenderQueue* queue = new GLRenderQueue(name, priority, GetPrimaryRenderTarget(), &m_globals);

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


int BaseOpenGLRenderer::GetShaderPropertyID(const char* name)
{
    return m_globals.GetPropertyID(name);
}

void BaseOpenGLRenderer::SetShaderFloat(const char* name, float value)
{
    m_globals.SetValue(name, value);
}

void BaseOpenGLRenderer::SetShaderVec2(const char* name, const vec2& value)
{
    m_globals.SetValue(name, value);
}

void BaseOpenGLRenderer::SetShaderVec3(const char* name, const vec3& value)
{
    m_globals.SetValue(name, value);
}

void BaseOpenGLRenderer::SetShaderVec4(const char* name, const vec4& value)
{
    m_globals.SetValue(name, value);
}

void BaseOpenGLRenderer::SetShaderMat4(const char* name, const mat4& value)
{
    m_globals.SetValue(name, value);
}

void BaseOpenGLRenderer::SetShaderInt(const char* name, int value)
{
    m_globals.SetValue(name, value);
}

void BaseOpenGLRenderer::SetShaderIVec2(const char* name, const ivec2& value)
{
    m_globals.SetValue(name, value);
}

void BaseOpenGLRenderer::SetShaderIVec3(const char* name, const ivec3& value)
{
    m_globals.SetValue(name, value);
}

void BaseOpenGLRenderer::SetShaderIVec4(const char* name, const ivec4& value)
{
    m_globals.SetValue(name, value);
}

void BaseOpenGLRenderer::SetShaderTexture1D(const char* name, Texture1D* texture)
{
    m_globals.SetValue(name, texture);
}

void BaseOpenGLRenderer::SetShaderTexture2D(const char* name, Texture2D* texture)
{
    m_globals.SetValue(name, texture);
}

void BaseOpenGLRenderer::SetShaderTexture3D(const char* name, Texture3D* texture)
{
    m_globals.SetValue(name, texture);
}

void BaseOpenGLRenderer::SetShaderFloat(int propertyID, float value)
{
    m_globals.SetValue(propertyID, value);
}

void BaseOpenGLRenderer::SetShaderVec2(int propertyID, const vec2& value)
{
    m_globals.SetValue(propertyID, value);
}

void BaseOpenGLRenderer::SetShaderVec3(int propertyID, const vec3& value)
{
    m_globals.SetValue(propertyID, value);
}

void BaseOpenGLRenderer::SetShaderVec4(int propertyID, const vec4& value)
{
    m_globals.SetValue(propertyID, value);
}

void BaseOpenGLRenderer::SetShaderMat4(int propertyID, const mat4& value)
{
    m_globals.SetValue(propertyID, value);
}

void BaseOpenGLRenderer::SetShaderInt(int propertyID, int value)
{
    m_globals.SetValue(propertyID, value);
}

void BaseOpenGLRenderer::SetShaderIVec2(int propertyID, const ivec2& value)
{
    m_globals.SetValue(propertyID, value);
}

void BaseOpenGLRenderer::SetShaderIVec3(int propertyID, const ivec3& value)
{
    m_globals.SetValue(propertyID, value);
}

void BaseOpenGLRenderer::SetShaderIVec4(int propertyID, const ivec4& value)
{
    m_globals.SetValue(propertyID, value);
}

void BaseOpenGLRenderer::SetShaderTexture1D(int propertyID, Texture1D* texture)
{
    m_globals.SetValue(propertyID, texture);
}

void BaseOpenGLRenderer::SetShaderTexture2D(int propertyID, Texture2D* texture)
{
    m_globals.SetValue(propertyID, texture);
}

void BaseOpenGLRenderer::SetShaderTexture3D(int propertyID, Texture3D* texture)
{
    m_globals.SetValue(propertyID, texture);
}


void BaseOpenGLRenderer::Present()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	for (size_t i = 0; i < m_renderQueues.size(); ++i)
		m_renderQueues[i]->FlushQueue();
    
	glFlush();
    SwapBuffers();
}

void BaseOpenGLRenderer::GameViewResized(const ivec2& size)
{
	m_primaryTarget.SetSize(size);
}
