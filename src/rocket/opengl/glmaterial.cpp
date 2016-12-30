#include "opengl/glmaterial.h"
#include "opengl/glshader.h"
#include "opengl/gltexture.h"
#include "opengl/glshaderglobals.h"
#include <cassert>

using namespace Rocket;
using namespace Rocket::OpenGL;

GLMaterial::GLMaterial(GLShader* shader) :
    m_shader(shader)
{
    assert(m_shader);
    
    const GLShader::Uniform* uniforms = shader->Uniforms();
    size_t numuniforms = shader->NumUniforms();
    
    m_parameters.resize(numuniforms);
    
    for (int i = 0; i < numuniforms; ++i)
    {
        const GLShader::Uniform* uniform = uniforms + i;
        m_parameters[i].name = uniform->name;
        m_parameters[i].location = uniform->location;
        m_parameters[i].globalID = uniform->globalID;
        m_parameters[i].type = VT_UNSET;
    }
}

GLMaterial::~GLMaterial()
{
    
}

void GLMaterial::SetShaderFloat(const char* name, float value)
{
    GLShaderValue v; v.f = value;
    SetByName(name, v, VT_FLOAT);
}

void GLMaterial::SetShaderVec2(const char* name, const vec2& value)
{
    GLShaderValue v; v.v2 = value;
    SetByName(name, v, VT_VEC2);
}

void GLMaterial::SetShaderVec3(const char* name, const vec3& value)
{
    GLShaderValue v; v.v3 = value;
    SetByName(name, v, VT_VEC3);
}

void GLMaterial::SetShaderVec4(const char* name, const vec4& value)
{
    GLShaderValue v; v.v4 = value;
    SetByName(name, v, VT_VEC4);
}

void GLMaterial::SetShaderMat4(const char* name, const mat4& value)
{
    GLShaderValue v; v.mat4 = value;
    SetByName(name, v, VT_MAT4);
}

void GLMaterial::SetShaderInt(const char* name, int value)
{
    GLShaderValue v; v.i = value;
    SetByName(name, v, VT_INT);
}

void GLMaterial::SetShaderIVec2(const char* name, const ivec2& value)
{
    GLShaderValue v; v.iv2 = value;
    SetByName(name, v, VT_IVEC2);
}

void GLMaterial::SetShaderIVec3(const char* name, const ivec3& value)
{
    GLShaderValue v; v.iv3 = value;
    SetByName(name, v, VT_IVEC3);
}

void GLMaterial::SetShaderIVec4(const char* name, const ivec4& value)
{
    GLShaderValue v; v.iv4 = value;
    SetByName(name, v, VT_IVEC4);
}

void GLMaterial::SetShaderTexture1D(const char* name, Texture1D* texture)
{
    GLShaderValue v; v.t1d = texture;
    SetByName(name, v, VT_TEXTURE1D);
}

void GLMaterial::SetShaderTexture2D(const char* name, Texture2D* texture)
{
    GLShaderValue v; v.t2d = texture;
    SetByName(name, v, VT_TEXTURE2D);
}

void GLMaterial::SetShaderTexture3D(const char* name, Texture3D* texture)
{
    GLShaderValue v; v.t3d = texture;
    SetByName(name, v, VT_TEXTURE3D);
}

void GLMaterial::SetShaderFloat(int propertyID, float value)
{
    GLShaderValue v; v.f = value;
    SetByID(propertyID, v, VT_FLOAT);
}

void GLMaterial::SetShaderVec2(int propertyID, const vec2& value)
{
    GLShaderValue v; v.v2 = value;
    SetByID(propertyID, v, VT_VEC2);
}

void GLMaterial::SetShaderVec3(int propertyID, const vec3& value)
{
    GLShaderValue v; v.v3 = value;
    SetByID(propertyID, v, VT_VEC3);
}

void GLMaterial::SetShaderVec4(int propertyID, const vec4& value)
{
    GLShaderValue v; v.v4 = value;
    SetByID(propertyID, v, VT_VEC4);
}

void GLMaterial::SetShaderMat4(int propertyID, const mat4& value)
{
    GLShaderValue v; v.mat4 = value;
    SetByID(propertyID, v, VT_MAT4);
}

void GLMaterial::SetShaderInt(int propertyID, int value)
{
    GLShaderValue v; v.i = value;
    SetByID(propertyID, v, VT_INT);
}

void GLMaterial::SetShaderIVec2(int propertyID, const ivec2& value)
{
    GLShaderValue v; v.iv2 = value;
    SetByID(propertyID, v, VT_IVEC2);
}

void GLMaterial::SetShaderIVec3(int propertyID, const ivec3& value)
{
    GLShaderValue v; v.iv3 = value;
    SetByID(propertyID, v, VT_IVEC3);
}

void GLMaterial::SetShaderIVec4(int propertyID, const ivec4& value)
{
    GLShaderValue v; v.iv4 = value;
    SetByID(propertyID, v, VT_IVEC4);
}

void GLMaterial::SetShaderTexture1D(int propertyID, Texture1D* texture)
{
    GLShaderValue v; v.t1d = texture;
    SetByID(propertyID, v, VT_TEXTURE1D);
}

void GLMaterial::SetShaderTexture2D(int propertyID, Texture2D* texture)
{
    GLShaderValue v; v.t2d = texture;
    SetByID(propertyID, v, VT_TEXTURE2D);
}

void GLMaterial::SetShaderTexture3D(int propertyID, Texture3D* texture)
{
    GLShaderValue v; v.t3d = texture;
    SetByID(propertyID, v, VT_TEXTURE3D);
}

void GLMaterial::ClearShaderProperty(const char *name)
{
    size_t size = m_parameters.size();
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(m_parameters[i].name, name) == 0)
        {
            m_parameters[i].type = VT_UNSET;
            return;
        }
    }
    // Not found..
}

void GLMaterial::ClearShaderProperty(int propertyID)
{
    size_t size = m_parameters.size();
    for (int i = 0; i < size; ++i)
    {
        if (m_parameters[i].globalID == propertyID)
        {
            m_parameters[i].type = VT_UNSET;
            return;
        }
    }
    // Not found..
}

void GLMaterial::SetByName(const char *name, GLShaderValue value, GLShaderValueType type)
{
    size_t size = m_parameters.size();
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(m_parameters[i].name, name) == 0)
        {
            m_parameters[i].value = value;
            m_parameters[i].type = type;
            return;
        }
    }
    // Not found..
}

void GLMaterial::SetByID(int propertyID, GLShaderValue value, GLShaderValueType type)
{
    size_t size = m_parameters.size();
    for (int i = 0; i < size; ++i)
    {
        if (m_parameters[i].globalID == propertyID)
        {
            m_parameters[i].value = value;
            m_parameters[i].type = type;
            return;
        }
    }
    
    // Not found..
}

void GLMaterial::MakeCurrent(GLShaderOverride* overrides)
{
    int activeTexture = 0;
    
    glUseProgram(m_shader->GetNativeHandle());
    
    size_t numParameters = m_parameters.size();
    for (int i = 0; i < numParameters; ++i)
    {
        Parameter& parameter = m_parameters[i];
        GLint location = parameter.location;
        
        GLShaderValueType type = parameter.type;
        const GLShaderValue* value = &parameter.value;
        
        if (type == VT_UNSET)
        {
            // get from globals
            const GLShaderProperty* overrideProperty = overrides->GetProperty(parameter.globalID);
            type = overrideProperty->type;
            value = &overrideProperty->value;
        }
        
        // TODO: type should be set with uniforms not per value set
        switch (type)
        {
            case VT_FLOAT:
            {
                glUniform1f(location, value->f);
                break;
            }
                
            case VT_VEC2:
            {
                glUniform2fv(location, 1, &value->v2.x);
                break;
            }
                
            case VT_VEC3:
            {
                glUniform3fv(location, 1, &value->v3.x);
                break;
            }
                
            case VT_VEC4:
            {
                glUniform4fv(location, 1, &value->v4.x);
                break;
            }
                
            case VT_MAT4:
            {
                glUniformMatrix4fv(location, 1, GL_TRUE, value->mat4.data());
                break;
            }
                
            case VT_INT:
            {
                glUniform1i(location, value->i);
                break;
            }
                
            case VT_IVEC2:
            {
                glUniform2iv(location, 1, &value->iv2.x);
                break;
            }
                
            case VT_IVEC3:
            {
                glUniform3iv(location, 1, &value->iv3.x);
                break;
            }
                
            case VT_IVEC4:
            {
                glUniform4iv(location, 1, &value->iv4.x);
                break;
            }
                
            case VT_TEXTURE1D:
            {
                GLint native = ((GLTexture1D*)value->t1d)->GetNativeHandle();
                glActiveTexture(GL_TEXTURE0+activeTexture);
                glBindTexture(GL_TEXTURE_1D, native);
                glUniform1i(location, activeTexture);
                activeTexture++;
                break;
            }
                
            case VT_TEXTURE2D:
            {
                GLint native = ((GLTexture2D*)value->t2d)->GetNativeHandle();
                glActiveTexture(GL_TEXTURE0+activeTexture);
                glBindTexture(GL_TEXTURE_2D, native);
                glUniform1i(location, activeTexture);
                activeTexture++;
                break;
            }
                
            case VT_TEXTURE3D:
            {
                GLint native = ((GLTexture3D*)value->t3d)->GetNativeHandle();
                glActiveTexture(GL_TEXTURE0+activeTexture);
                glBindTexture(GL_TEXTURE_3D, native);
                glUniform1i(location, activeTexture);
                activeTexture++;
                break;
            }
            
            case VT_UNSET:
            {
                // Unassigned parameter
                break;
            }
                
            default:
            {
                assert(false); // Unhandled parameter type
                break;
            }
        }
    }
}
