#include "opengl/glrenderqueue.h"
#include "opengl/rocket_opengl.h"
#include "opengl/glmaterial.h"
#include "opengl/gldrawbinding.h"
#include "opengl/glrendertarget.h"

#include <cassert>


using namespace Rocket;
using namespace Rocket::OpenGL;

GLRenderQueue::GLRenderQueue(const char* name, int priority, RenderTarget* defaultTarget, GLShaderGlobals* globals) :
    m_globals(globals),
    m_name(name),
	m_priority(priority),
	m_enabled(true),
	m_clearColorEnabled(false),
	m_clearColor(0, 0, 0, 1),
	m_clearDepthEnabled(false),
	m_clearDepth(1.0f),
	m_depthTestEnabled(true),
	m_target(defaultTarget)
{
	m_viewport = ViewportRect { vec2::Zero(), vec2::One() };
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
	m_depthTestEnabled = enabled;
}

bool GLRenderQueue::IsDepthTestEnabled() const
{
	return m_depthTestEnabled;
}

void GLRenderQueue::SetTarget(RenderTarget* target)
{
	m_target = target;
}

RenderTarget* GLRenderQueue::GetTarget()
{
	return m_target;
}

void GLRenderQueue::SetViewport(const ViewportRect& viewport)
{
	m_viewport = viewport;
}

ViewportRect GLRenderQueue::GetViewport() const
{
	return m_viewport;
}

void GLRenderQueue::SetShaderFloat(const char* name, float value)
{
    SetShaderFloat(m_globals->GetPropertyID(name), value);
}

void GLRenderQueue::SetShaderVec2(const char* name, const vec2& value)
{
    SetShaderVec2(m_globals->GetPropertyID(name), value);
}

void GLRenderQueue::SetShaderVec3(const char* name, const vec3& value)
{
    SetShaderVec3(m_globals->GetPropertyID(name), value);
}

void GLRenderQueue::SetShaderVec4(const char* name, const vec4& value)
{
    SetShaderVec4(m_globals->GetPropertyID(name), value);
}

void GLRenderQueue::SetShaderMat4(const char* name, const mat4& value)
{
    SetShaderMat4(m_globals->GetPropertyID(name), value);
}

void GLRenderQueue::SetShaderInt(const char* name, int value)
{
    SetShaderInt(m_globals->GetPropertyID(name), value);
}

void GLRenderQueue::SetShaderIVec2(const char* name, const ivec2& value)
{
    SetShaderIVec2(m_globals->GetPropertyID(name), value);
}

void GLRenderQueue::SetShaderIVec3(const char* name, const ivec3& value)
{
    SetShaderIVec3(m_globals->GetPropertyID(name), value);
}

void GLRenderQueue::SetShaderIVec4(const char* name, const ivec4& value)
{
    SetShaderIVec4(m_globals->GetPropertyID(name), value);
}

void GLRenderQueue::SetShaderTexture1D(const char* name, Texture1D* texture)
{
    SetShaderTexture1D(m_globals->GetPropertyID(name), texture);
}

void GLRenderQueue::SetShaderTexture2D(const char* name, Texture2D* texture)
{
    SetShaderTexture2D(m_globals->GetPropertyID(name), texture);
}

void GLRenderQueue::SetShaderTexture3D(const char* name, Texture3D* texture)
{
    SetShaderTexture3D(m_globals->GetPropertyID(name), texture);
}

void GLRenderQueue::SetShaderFloat(int propertyID, float value)
{
    GLShaderProperty property;
    property.type = VT_FLOAT;
    property.value.f = value;
    SetProperty(propertyID, property);
}

void GLRenderQueue::SetShaderVec2(int propertyID, const vec2& value)
{
    GLShaderProperty property;
    property.type = VT_VEC2;
    property.value.v2 = value;
    SetProperty(propertyID, property);
}

void GLRenderQueue::SetShaderVec3(int propertyID, const vec3& value)
{
    GLShaderProperty property;
    property.type = VT_VEC3;
    property.value.v3 = value;
    SetProperty(propertyID, property);
}

void GLRenderQueue::SetShaderVec4(int propertyID, const vec4& value)
{
    GLShaderProperty property;
    property.type = VT_VEC4;
    property.value.v4 = value;
    SetProperty(propertyID, property);
}

void GLRenderQueue::SetShaderMat4(int propertyID, const mat4& value)
{
    GLShaderProperty property;
    property.type = VT_MAT4;
    property.value.mat4 = value;
    SetProperty(propertyID, property);
}

void GLRenderQueue::SetShaderInt(int propertyID, int value)
{
    GLShaderProperty property;
    property.type = VT_INT;
    property.value.i = value;
    SetProperty(propertyID, property);
}

void GLRenderQueue::SetShaderIVec2(int propertyID, const ivec2& value)
{
    GLShaderProperty property;
    property.type = VT_IVEC2;
    property.value.iv2 = value;
    SetProperty(propertyID, property);
}

void GLRenderQueue::SetShaderIVec3(int propertyID, const ivec3& value)
{
    GLShaderProperty property;
    property.type = VT_IVEC3;
    property.value.iv3 = value;
    SetProperty(propertyID, property);
}

void GLRenderQueue::SetShaderIVec4(int propertyID, const ivec4& value)
{
    GLShaderProperty property;
    property.type = VT_IVEC4;
    property.value.iv4 = value;
    SetProperty(propertyID, property);
}

void GLRenderQueue::SetShaderTexture1D(int propertyID, Texture1D* texture)
{
    GLShaderProperty property;
    property.type = VT_TEXTURE1D;
    property.value.t1d = texture;
    SetProperty(propertyID, property);
}

void GLRenderQueue::SetShaderTexture2D(int propertyID, Texture2D* texture)
{
    GLShaderProperty property;
    property.type = VT_TEXTURE2D;
    property.value.t2d = texture;
    SetProperty(propertyID, property);
}

void GLRenderQueue::SetShaderTexture3D(int propertyID, Texture3D* texture)
{
    GLShaderProperty property;
    property.type = VT_TEXTURE3D;
    property.value.t3d = texture;
    SetProperty(propertyID, property);
}

void GLRenderQueue::ClearShaderProperty(const char* name)
{
    ClearShaderProperty(m_globals->GetPropertyID(name));
}

void GLRenderQueue::ClearShaderProperty(int propertyID)
{
    int index = -1;
    
    for(int i = 0; i < (int)m_propertyIDs.size(); ++i)
    {
        if (m_propertyIDs[i] == propertyID)
        {
            index = i;
            break;
        }
    }
    
    assert(index >= 0); // Index not found
    
    m_propertyIDs.erase(m_propertyIDs.begin() + index);
    m_properties.erase(m_properties.begin() + index);
}

const GLShaderProperty* GLRenderQueue::GetProperty(int propertyID) const
{
    int index = -1;
    int size = (int)m_propertyIDs.size();
    for (int i = 0; i < size; ++i)
    {
        if (m_propertyIDs[i] == propertyID)
        {
            index = i;
            break;
        }
    }
    
    if (index < 0)
        return m_globals->GetProperty(propertyID);
    
    return &m_properties[index];
}

void GLRenderQueue::FlushQueue()
{
	if (m_enabled)
	{
		GLenum clearFlags = 0;

		glBindFramebuffer(GL_FRAMEBUFFER, ((GLRenderTarget*)m_target)->GetNativeHandle());

		ivec2 isize = m_target->GetSize();
		vec2 size = vec2((float)isize.x, (float)isize.y);
		ViewportRect viewport = ViewportRect{ m_viewport.origin * size, m_viewport.size * size };

		glViewport((GLint)viewport.origin.x, (GLint)viewport.origin.y, (GLint)viewport.size.x, (GLint)viewport.size.y);

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

			GLMaterial* material = (GLMaterial*)draw.material;
            material->MakeCurrent((GLShaderOverride*)this);
            
			((GLDrawBinding*)draw.binding)->Draw();
		}
	}

	m_drawQueue.clear();
}

void GLRenderQueue::SetProperty(int propertyID, GLShaderProperty& property)
{
    int index = -1;
    int size = (int)m_propertyIDs.size();
    
    for (int i = 0; i < size; ++i)
    {
        if (m_propertyIDs[i] == propertyID)
        {
            index = i;
            break;
        }
    }
    
    if (index < 0)
    {
        m_propertyIDs.push_back(propertyID);
        m_properties.push_back(property);
    }
    else
    {
        m_properties[index] = property;
    }
}
