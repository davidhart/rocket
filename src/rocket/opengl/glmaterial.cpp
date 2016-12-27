#include "opengl/glmaterial.h"
#include "opengl/glshader.h"
#include "opengl/gltexture.h"
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

void GLMaterial::SetFloat(const char* name, float value)
{
    GLShaderValue v; v.f = value;
    SetByName(name, v, VT_FLOAT);
}

void GLMaterial::SetVec2(const char* name, const vec2& value)
{
    GLShaderValue v; v.v2 = value;
    SetByName(name, v, VT_VEC2);
}

void GLMaterial::SetVec3(const char* name, const vec3& value)
{
    GLShaderValue v; v.v3 = value;
    SetByName(name, v, VT_VEC3);
}

void GLMaterial::SetVec4(const char* name, const vec4& value)
{
    GLShaderValue v; v.v4 = value;
    SetByName(name, v, VT_VEC4);
}

void GLMaterial::SetMat4(const char* name, const mat4& value)
{
    GLShaderValue v; v.mat4 = value;
    SetByName(name, v, VT_MAT4);
}

void GLMaterial::SetInt(const char* name, int value)
{
    GLShaderValue v; v.i = value;
    SetByName(name, v, VT_INT);
}

void GLMaterial::SetIVec2(const char* name, const ivec2& value)
{
    GLShaderValue v; v.iv2 = value;
    SetByName(name, v, VT_IVEC2);
}

void GLMaterial::SetIVec3(const char* name, const ivec3& value)
{
    GLShaderValue v; v.iv3 = value;
    SetByName(name, v, VT_IVEC3);
}

void GLMaterial::SetIVec4(const char* name, const ivec4& value)
{
    GLShaderValue v; v.iv4 = value;
    SetByName(name, v, VT_IVEC4);
}

void GLMaterial::SetTexture1D(const char* name, Texture1D* texture)
{
    GLShaderValue v; v.t1d = texture;
    SetByName(name, v, VT_TEXTURE1D);
}

void GLMaterial::SetTexture2D(const char* name, Texture2D* texture)
{
    GLShaderValue v; v.t2d = texture;
    SetByName(name, v, VT_TEXTURE2D);
}

void GLMaterial::SetTexture3D(const char* name, Texture3D* texture)
{
    GLShaderValue v; v.t3d = texture;
    SetByName(name, v, VT_TEXTURE3D);
}

void GLMaterial::SetFloat(int propertyID, float value)
{
    GLShaderValue v; v.f = value;
    SetByID(propertyID, v, VT_FLOAT);
}

void GLMaterial::SetVec2(int propertyID, const vec2& value)
{
    GLShaderValue v; v.v2 = value;
    SetByID(propertyID, v, VT_VEC2);
}

void GLMaterial::SetVec3(int propertyID, const vec3& value)
{
    GLShaderValue v; v.v3 = value;
    SetByID(propertyID, v, VT_VEC3);
}

void GLMaterial::SetVec4(int propertyID, const vec4& value)
{
    GLShaderValue v; v.v4 = value;
    SetByID(propertyID, v, VT_VEC4);
}

void GLMaterial::SetMat4(int propertyID, const mat4& value)
{
    GLShaderValue v; v.mat4 = value;
    SetByID(propertyID, v, VT_MAT4);
}

void GLMaterial::SetInt(int propertyID, int value)
{
    GLShaderValue v; v.i = value;
    SetByID(propertyID, v, VT_INT);
}

void GLMaterial::SetIVec2(int propertyID, const ivec2& value)
{
    GLShaderValue v; v.iv2 = value;
    SetByID(propertyID, v, VT_IVEC2);
}

void GLMaterial::SetIVec3(int propertyID, const ivec3& value)
{
    GLShaderValue v; v.iv3 = value;
    SetByID(propertyID, v, VT_IVEC3);
}

void GLMaterial::SetIVec4(int propertyID, const ivec4& value)
{
    GLShaderValue v; v.iv4 = value;
    SetByID(propertyID, v, VT_IVEC4);
}

void GLMaterial::SetTexture1D(int propertyID, Texture1D* texture)
{
    GLShaderValue v; v.t1d = texture;
    SetByID(propertyID, v, VT_TEXTURE1D);
}

void GLMaterial::SetTexture2D(int propertyID, Texture2D* texture)
{
    GLShaderValue v; v.t2d = texture;
    SetByID(propertyID, v, VT_TEXTURE2D);
}

void GLMaterial::SetTexture3D(int propertyID, Texture3D* texture)
{
    GLShaderValue v; v.t3d = texture;
    SetByID(propertyID, v, VT_TEXTURE3D);
}

void GLMaterial::Clear(const char *name)
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

void GLMaterial::Clear(int propertyID)
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

void GLMaterial::MakeCurrent(GLShaderGlobals* globals)
{
    int activeTexture = 0;
    
    glUseProgram(m_shader->GetNativeHandle());
    
    size_t numParameters = m_parameters.size();
    for (int i = 0; i < numParameters; ++i)
    {
        Parameter& parameter = m_parameters[i];
        GLint location = parameter.location;
        
        switch (parameter.type)
        {
            case VT_FLOAT:
            {
                glUniform1f(location, parameter.value.f);
                break;
            }
                
            case VT_VEC2:
            {
                glUniform2fv(location, 1, &parameter.value.v2.x);
                break;
            }
                
            case VT_VEC3:
            {
                glUniform3fv(location, 1, &parameter.value.v3.x);
                break;
            }
                
            case VT_VEC4:
            {
                glUniform4fv(location, 1, &parameter.value.v4.x);
                break;
            }
                
            case VT_MAT4:
            {
                glUniformMatrix4fv(location, 1, GL_TRUE, parameter.value.mat4.data());
                break;
            }
                
            case VT_INT:
            {
                glUniform1i(location, parameter.value.i);
                break;
            }
                
            case VT_IVEC2:
            {
                glUniform2iv(location, 1, &parameter.value.iv2.x);
                break;
            }
                
            case VT_IVEC3:
            {
                glUniform3iv(location, 1, &parameter.value.iv3.x);
                break;
            }
                
            case VT_IVEC4:
            {
                glUniform4iv(location, 1, &parameter.value.iv4.x);
                break;
            }
                
            case VT_TEXTURE1D:
            {
                GLint native = ((GLTexture1D*)parameter.value.t1d)->GetNativeHandle();
                glActiveTexture(GL_TEXTURE0+activeTexture);
                glBindTexture(GL_TEXTURE_1D, native);
                glUniform1i(parameter.location, activeTexture);
                activeTexture++;
                break;
            }
                
            case VT_TEXTURE2D:
            {
                GLint native = ((GLTexture2D*)parameter.value.t2d)->GetNativeHandle();
                glActiveTexture(GL_TEXTURE0+activeTexture);
                glBindTexture(GL_TEXTURE_2D, native);
                glUniform1i(parameter.location, activeTexture);
                activeTexture++;
                break;
            }
                
            case VT_TEXTURE3D:
            {
                GLint native = ((GLTexture3D*)parameter.value.t3d)->GetNativeHandle();
                glActiveTexture(GL_TEXTURE0+activeTexture);
                glBindTexture(GL_TEXTURE_3D, native);
                glUniform1i(parameter.location, activeTexture);
                activeTexture++;
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
