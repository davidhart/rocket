#include "glshader.h"

#include <cstdio>

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

	return true;
}

GLuint GLShader::GetNativeHandle()
{
	return m_program;
}

GLenum GLShader::CreateSubShader(GLenum type, size_t size, const void* source)
{
	GLenum shader = glCreateShader(type);

	const GLchar* glsource = (const GLchar*)source;

	glShaderSource(shader, 1, &glsource, nullptr);
	glCompileShader(shader);
	
	int compileStatus = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == GL_FALSE)
	{
		int infoLogLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

		char* log = (char*)malloc(infoLogLen);
		glGetShaderInfoLog(shader, infoLogLen, &infoLogLen, log);
		std::fprintf(stderr, "Shader compile errors: \n %s\n", log);
		free(log);
	}

	return shader;
}