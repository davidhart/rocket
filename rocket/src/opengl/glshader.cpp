#include "glshader.h"

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

bool GLShader::Create(const ShaderSource& source)
{
	m_vert = CreateSubShader(GL_VERTEX_SHADER, source.vertSize, source.vert);

	m_frag = CreateSubShader(GL_FRAGMENT_SHADER, source.fragSize, source.frag);

	m_program = glCreateProgram();
	glAttachShader(m_program, m_vert);
	glAttachShader(m_program, m_frag);
	glLinkProgram(m_program);

	return true;
}

GLenum GLShader::CreateSubShader(GLenum type, size_t size, const void* source)
{
	GLenum shader = glCreateShader(type);

	const GLchar* glsource = (const GLchar*)source;
	GLint glsize = (GLint)size;

	glShaderSource(shader, 1, &glsource, &glsize);
	glCompileShader(shader);

	return shader;
}