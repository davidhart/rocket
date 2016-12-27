#include "opengl/glshaderglobals.h"
#include <cstring>

using namespace Rocket;
using namespace Rocket::OpenGL;

GLShaderValue::GLShaderValue()
{
    memset(this, '\0', sizeof(GLShaderValue));
}

int GLShaderGlobals::AddProperty(const char* name)
{
    std::string name_str(name);
    
    auto it = m_nameToIndex.find(name_str);
    
    if (it != m_nameToIndex.end())
    {
        return it->second;
    }
    
    Property property;
    property.name = name;
    property.type = VT_UNSET;
    m_properties.push_back(property);
    
    int index = m_properties.size() - 1;
    m_nameToIndex[name] = index;
    
    return index;
}

int GLShaderGlobals::GetPropertyID(const char* name)
{
    return AddProperty(name);
}

void GLShaderGlobals::SetValue(const char* name, float value)
{
    int id = GetPropertyID(name);
    SetValue(id, value);
}

void GLShaderGlobals::SetValue(const char* name, const vec2& value)
{
    int id = GetPropertyID(name);
    SetValue(id, value);
}

void GLShaderGlobals::SetValue(const char* name, const vec3& value)
{
    int id = GetPropertyID(name);
    SetValue(id, value);
}

void GLShaderGlobals::SetValue(const char* name, const vec4& value)
{
    int id = GetPropertyID(name);
    SetValue(id, value);
}

void GLShaderGlobals::SetValue(const char* name, const mat4& value)
{
    int id = GetPropertyID(name);
    SetValue(id, value);
}

void GLShaderGlobals::SetValue(const char* name, int value)
{
    int id = GetPropertyID(name);
    SetValue(id, value);
}

void GLShaderGlobals::SetValue(const char* name, const ivec2& value)
{
    int id = GetPropertyID(name);
    SetValue(id, value);
}

void GLShaderGlobals::SetValue(const char* name, const ivec3& value)
{
    int id = GetPropertyID(name);
    SetValue(id, value);
}

void GLShaderGlobals::SetValue(const char* name, const ivec4& value)
{
    int id = GetPropertyID(name);
    SetValue(id, value);
}

void GLShaderGlobals::SetValue(const char* name, Texture1D* texture)
{
    int id = GetPropertyID(name);
    SetValue(id, texture);
}

void GLShaderGlobals::SetValue(const char* name, Texture2D* texture)
{
    int id = GetPropertyID(name);
    SetValue(id, texture);
}

void GLShaderGlobals::SetValue(const char* name, Texture3D* texture)
{
    int id = GetPropertyID(name);
    SetValue(id, texture);
}

void GLShaderGlobals::SetValue(int propertyID, float value)
{
    Property& p = m_properties[propertyID];
    p.value.f = value;
    p.type = VT_FLOAT;
}

void GLShaderGlobals::SetValue(int propertyID, const vec2& value)
{
    Property& p = m_properties[propertyID];
    p.value.v2 = value;
    p.type = VT_VEC2;
}

void GLShaderGlobals::SetValue(int propertyID, const vec3& value)
{
    Property& p = m_properties[propertyID];
    p.value.v3 = value;
    p.type = VT_VEC3;
}

void GLShaderGlobals::SetValue(int propertyID, const vec4& value)
{
    Property& p = m_properties[propertyID];
    p.value.v4 = value;
    p.type = VT_VEC4;
}

void GLShaderGlobals::SetValue(int propertyID, const mat4& value)
{
    Property& p = m_properties[propertyID];
    p.value.mat4 = value;
    p.type = VT_MAT4;
}

void GLShaderGlobals::SetValue(int propertyID, int value)
{
    Property& p = m_properties[propertyID];
    p.value.i = value;
    p.type = VT_INT;
}

void GLShaderGlobals::SetValue(int propertyID, const ivec2& value)
{
    Property& p = m_properties[propertyID];
    p.value.iv2 = value;
    p.type = VT_IVEC2;
}

void GLShaderGlobals::SetValue(int propertyID, const ivec3& value)
{
    Property& p = m_properties[propertyID];
    p.value.iv3 = value;
    p.type = VT_IVEC3;
}

void GLShaderGlobals::SetValue(int propertyID, const ivec4& value)
{
    Property& p = m_properties[propertyID];
    p.value.iv4 = value;
    p.type = VT_IVEC4;
}

void GLShaderGlobals::SetValue(int propertyID, Texture1D* texture)
{
    Property& p = m_properties[propertyID];
    p.value.t1d = texture;
    p.type = VT_TEXTURE1D;
}

void GLShaderGlobals::SetValue(int propertyID, Texture2D* texture)
{
    Property& p = m_properties[propertyID];
    p.value.t2d = texture;
    p.type = VT_TEXTURE2D;
}

void GLShaderGlobals::SetValue(int propertyID, Texture3D* texture)
{
    Property& p = m_properties[propertyID];
    p.value.t3d = texture;
    p.type = VT_TEXTURE3D;
}
