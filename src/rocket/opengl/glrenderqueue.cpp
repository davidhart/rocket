#include "opengl/glrenderqueue.h"

#include "material.h"
#include "opengl/rocket_opengl.h"
#include "opengl/glshader.h"
#include "opengl/gldrawbinding.h"

using namespace Rocket;
using namespace Rocket::OpenGL;

GLRenderQueue::GLRenderQueue(const char* name, int priority) :
	m_name(name),
	m_priority(priority),
	m_enabled(true),
	m_clearColorEnabled(false),
	m_clearColor(0, 0, 0, 1),
	m_clearDepthEnabled(false),
	m_clearDepth(1.0f),
	m_depthTestEnabled(true)
{
}

void GLRenderQueue::Draw(DrawBinding* drawBinding, Material* material)
{
	QueueItem qi;
	qi.binding = drawBinding;
	qi.material = material;
	m_drawQueue.push_back(qi);
}

const char* GLRenderQueue::Name() const
{
	return m_name.c_str();
}

int GLRenderQueue::Priority() const
{
	return m_priority;
}

void GLRenderQueue::SetEnabled(bool enabled)
{
	m_enabled = enabled;
}

bool GLRenderQueue::IsEnabled() const
{
	return m_enabled;
}

void GLRenderQueue::SetClearColorEnabled(bool enabled)
{
	m_clearColorEnabled = enabled;
}

bool GLRenderQueue::IsClearColorEnabled() const
{
	return m_clearColorEnabled;
}

void GLRenderQueue::SetClearColor(color color)
{
	m_clearColor = color;
}

void GLRenderQueue::SetClearDepthEnabled(bool enabled)
{
	m_clearDepthEnabled = enabled;
}

bool GLRenderQueue::IsClearDepthEnabled() const
{
	return m_clearDepthEnabled;
}

void GLRenderQueue::SetClearDepth(float depth)
{
	m_clearDepth = depth;
}

void GLRenderQueue::SetDepthTestEnabled(bool enabled)
{
	m_clearDepthEnabled = enabled;
}

bool GLRenderQueue::IsDepthTestEnabled() const
{
	return m_clearDepthEnabled;
}

void GLRenderQueue::FlushQueue()
{
	if (m_enabled)
	{
		GLenum clearFlags = 0;

		if (m_clearColorEnabled)
		{
			glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.z);
			clearFlags |= GL_COLOR_BUFFER_BIT;
		}

		if (m_clearDepthEnabled)
		{
			glClearDepth(m_clearDepth);
			clearFlags |= GL_DEPTH_BUFFER_BIT;
		}

		if (clearFlags)
		{
			glClear(clearFlags);
		}

		if (m_depthTestEnabled)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

		for (size_t i = 0; i < m_drawQueue.size(); ++i)
		{
			QueueItem draw = m_drawQueue[i];

			Material* material = draw.material;

			GLuint shaderhandle = ((GLShader*)material->GetShader())->GetNativeHandle();
			glUseProgram(shaderhandle);

			GLShaderParameters* parameters = (GLShaderParameters*)material->GetParameters();
			parameters->MakeCurrent();

			((GLDrawBinding*)draw.binding)->Draw();
		}
	}

	m_drawQueue.clear();
}
