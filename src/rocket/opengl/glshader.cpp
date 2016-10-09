#include "opengl/glshader.h"

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

ParameterData::ParameterData() :
	location(-1),
	value{ 0 },
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
	ParameterData data;
	data.location = m_shader->GetParameterLocation(name);
	data.value.f = value;
	data.setter = &set1f;

	m_parameters[name] = data;
}

void set2f(const ParameterData& data)
{
	glUniform2f(data.location, data.value.v2.x, data.value.v2.y);
}

void GLShaderParameters::SetVec2(const char* name, const vec2& value)
{
	ParameterData data;
	data.location = m_shader->GetParameterLocation(name);
	data.value.v2 = value;
	data.setter = &set2f;

	m_parameters[name] = data;
}

void set3f(const ParameterData& data)
{
	glUniform3f(data.location, data.value.v3.x, data.value.v3.y, data.value.v3.z);
}

void GLShaderParameters::SetVec3(const char* name, const vec3& value)
{
	ParameterData data;
	data.location = m_shader->GetParameterLocation(name);
	data.value.v3 = value;
	data.setter = &set3f;

	m_parameters[name] = data;
}

void set4f(const ParameterData& data)
{
	glUniform4f(data.location, data.value.v4.x, data.value.v4.y, data.value.v4.z, data.value.v4.w);
}

void GLShaderParameters::SetVec4(const char* name, const vec4& value)
{
	ParameterData data;
	data.location = m_shader->GetParameterLocation(name);
	data.value.v4 = value;
	data.setter = &set4f;

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
}