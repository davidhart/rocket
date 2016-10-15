#include "opengl/glshader.h"
#include "opengl/gltexture.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <map>
#include <iostream>

using namespace Rocket;
using namespace Rocket::OpenGL;

GLShader::GLShader() :
	m_program(0),
	m_vert(0),
	m_frag(0)
{

}

GLShader::~GLShader()
{
	if (m_program != 0)
	{
		glDeleteProgram(m_program);
	}

	if (m_vert != 0)
	{
		glDeleteShader(m_vert);
	}

	if (m_frag != 0)
	{
		glDeleteShader(m_frag);
	}
}

bool GLShader::Create(const ShaderDef& source)
{
	m_vert = CreateSubShader(GL_VERTEX_SHADER, source.vertSize, source.vert);

	m_frag = CreateSubShader(GL_FRAGMENT_SHADER, source.fragSize, source.frag);

	m_program = glCreateProgram();
	glAttachShader(m_program, m_vert);
	glAttachShader(m_program, m_frag);
	glLinkProgram(m_program);

	glUseProgram(m_program);
	glUseProgram(0);


	GLint activeUniforms;
	glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &activeUniforms);

	for (int i = 0; i < activeUniforms; ++i)
	{
		GLint size;
		GLenum type;

		GLchar name[256];
		int nameLength = 0;

		glGetActiveUniform(m_program, i, sizeof(name), &nameLength, &size, &type, name);

		GLint location = glGetUniformLocation(m_program, name);
		m_shaderParameterLocations[std::string(name, nameLength)] = location;
	}

	return true;
}

ShaderParameters* GLShader::CreateParameters()
{
	return new GLShaderParameters(this);
}

void GLShader::ReleaseParameters(ShaderParameters* parameters)
{
	delete parameters;
}

GLuint GLShader::GetNativeHandle()
{
	return m_program;
}

GLint GLShader::GetParameterLocation(const char* name)
{
	auto it = m_shaderParameterLocations.find(name);

	if (it == m_shaderParameterLocations.end())
	{
		return -1;
	}

	return it->second;
}

GLenum GLShader::CreateSubShader(GLenum type, unsigned, const void* source)
{
	GLenum shader = glCreateShader(type);

	const GLchar* glsource = (const GLchar*)source;

	glShaderSource(shader, 1, &glsource, nullptr);
	glCompileShader(shader);
	
	GLint compileStatus = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == GL_FALSE)
	{
		GLint infoLogLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

        char* log = (char*)malloc(infoLogLen);
		glGetShaderInfoLog(shader, infoLogLen, &infoLogLen, log);
		std::fprintf(stderr, "Shader compile errors: \n %s\n", log);
        free(log);
	}

	return shader;
}

ParameterValue::ParameterValue()
{
	// Intentionally uninitialized
}

ParameterData::ParameterData() :
	location(-1),
	setter(nullptr)
{
}

GLShaderParameters::GLShaderParameters(GLShader* shader) :
	m_shader(shader)
{
}

void set1f(const ParameterData& data)
{
	glUniform1f(data.location, data.value.f);
}

void GLShaderParameters::SetFloat(const char* name, float value)
{
	ParameterValue pv;
	pv.f = value;
	Set(name, pv, &set1f);
}

void set2f(const ParameterData& data)
{
	glUniform2f(data.location, data.value.v2.x, data.value.v2.y);
}

void GLShaderParameters::SetVec2(const char* name, const vec2& value)
{
	ParameterValue pv;
	pv.v2 = value;
	Set(name, pv, &set2f);
}

void set3f(const ParameterData& data)
{
	glUniform3f(data.location, data.value.v3.x, data.value.v3.y, data.value.v3.z);
}

void GLShaderParameters::SetVec3(const char* name, const vec3& value)
{
	ParameterValue pv;
	pv.v3 = value;
	Set(name, pv, &set3f);
}

void set4f(const ParameterData& data)
{
	glUniform4f(data.location, data.value.v4.x, data.value.v4.y, data.value.v4.z, data.value.v4.w);
}

void GLShaderParameters::SetVec4(const char* name, const vec4& value)
{
	ParameterValue pv;
	pv.v4 = value;
	Set(name, pv, &set4f);
}

void setmat4f(const ParameterData& data)
{
	glUniformMatrix4fv(data.location, 1, GL_FALSE, data.value.mat4.data());
}

void GLShaderParameters::SetMat4(const char* name, const mat4& value)
{
	ParameterValue pv;
	pv.mat4 = value;
	Set(name, pv, &setmat4f);
}

void set1i(const ParameterData& data)
{
	glUniform1i(data.location, data.value.i);
}

void GLShaderParameters::SetInt(const char* name, int value)
{
	ParameterValue pv;
	pv.i = value;
	Set(name, pv, &set1i);
}

void set2i(const ParameterData& data)
{
	glUniform2i(data.location, data.value.iv2.x, data.value.iv2.y);
}

void GLShaderParameters::SetIVec2(const char* name, const ivec2& value)
{
	ParameterValue pv;
	pv.iv2 = value;
	Set(name, pv, &set2i);
}

void set3i(const ParameterData& data)
{
	glUniform3i(data.location, data.value.iv3.x, data.value.iv3.y, data.value.iv3.z);
}

void GLShaderParameters::SetIVec3(const char* name, const ivec3& value)
{
	ParameterValue pv;
	pv.iv3 = value;
	Set(name, pv, &set3i);
}

void set4i(const ParameterData& data)
{
	glUniform4i(data.location, data.value.iv4.x, data.value.iv4.y, data.value.iv4.z, data.value.iv4.w);
}

void GLShaderParameters::SetIVec4(const char* name, const ivec4& value)
{
	ParameterValue pv;
	pv.iv4 = value;
	Set(name, pv, &set4i);
}

void GLShaderParameters::SetTexture1D(const char* name, Texture1D* texture)
{
	m_samplers1D[name] = { m_shader->GetParameterLocation(name), texture };
}

void GLShaderParameters::SetTexture2D(const char* name, Texture2D* texture)
{
	m_samplers2D[name] = { m_shader->GetParameterLocation(name), texture };
}

void GLShaderParameters::SetTexture3D(const char* name, Texture3D* texture)
{
	m_samplers3D[name] = { m_shader->GetParameterLocation(name), texture };
}

void GLShaderParameters::Set(const char* name, const ParameterValue& value, SetFunc func)
{
	ParameterData data;
	data.location = m_shader->GetParameterLocation(name);
	data.value = value;
	data.setter = func;
	m_parameters[name] = data;
}


void GLShaderParameters::MakeCurrent()
{
	for (auto it = m_parameters.begin(); it != m_parameters.end(); ++it)
	{
		ParameterData data = it->second;

		if (data.location >= 0)
		{
			it->second.setter(data);
		}
	}

	int sampler = 0;
    
	for (auto it = m_samplers1D.begin(); it != m_samplers1D.end(); ++it)
	{
		glActiveTexture(GL_TEXTURE0 + sampler);
		glBindTexture(GL_TEXTURE_1D, ((GLTexture1D*)it->second.texture)->GetNativeHandle());
		glUniform1i(it->second.location, sampler);
        sampler++;
	}
    
    for (auto it = m_samplers2D.begin(); it != m_samplers2D.end(); ++it)
    {
        glActiveTexture(GL_TEXTURE0 + sampler);
        glBindTexture(GL_TEXTURE_2D, ((GLTexture2D*)it->second.texture)->GetNativeHandle());
        glUniform1i(it->second.location, sampler);
        sampler++;
    }
    
    for (auto it = m_samplers3D.begin(); it != m_samplers3D.end(); ++it)
    {
        glActiveTexture(GL_TEXTURE0 + sampler);
        glBindTexture(GL_TEXTURE_3D, ((GLTexture3D*)it->second.texture)->GetNativeHandle());
        glUniform1i(it->second.location, sampler);
        sampler++;
    }
}
