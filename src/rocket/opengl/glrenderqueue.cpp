#include "opengl/glrenderqueue.h"

#include "material.h"
#include "opengl/rocket_opengl.h"
#include "opengl/glshader.h"
#include "opengl/gldrawbinding.h"

using namespace Rocket;
using namespace Rocket::OpenGL;

GLRenderQueue::GLRenderQueue(const char* name) :
	m_name(name),
	m_enabled(true)
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
void GLRenderQueue::SetEnabled(bool enabled)
{
	m_enabled = enabled;
}
bool GLRenderQueue::IsEnabled() const
{
	return m_enabled;
}

void GLRenderQueue::FlushQueue()
{
	glClearColor(0.3f, 0.05f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

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

	m_drawQueue.clear();
}