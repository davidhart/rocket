#include "glshader.h"

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

bool GLShader::Create(size_t size, void* data)
{
	m_vert = glCreateShader(GL_VERTEX_SHADER);
	m_frag = glCreateShader(GL_FRAGMENT_SHADER);

	m_program = glCreateProgram();
	glAttachShader(m_program, m_vert);
	glAttachShader(m_program, m_frag);
	glLinkProgram(m_program);

	return true;
}