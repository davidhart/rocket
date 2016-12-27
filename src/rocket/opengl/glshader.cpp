#include "opengl/glshader.h"
#include "opengl/gltexture.h"
#include "opengl/glshaderglobals.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>

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
    
    for (size_t i = 0; i < m_parameters.size(); ++i)
    {
        free(m_parameters[i].name);
    }
}

bool GLShader::Create(const ShaderDef& source, GLShaderGlobals& globals)
{
	if (CreateInternal(source, globals))
		return true;
	
	const char vertSource[] =
		"#version 140\n"
		"#extension GL_ARB_explicit_attrib_location : enable\n"
		"uniform mat4 u_transform;\n"
		"layout(location=0)in vec3 i_vert;\n"
		"void main() {\n"
		"vec4 temp;\n"
		"temp.xyz = i_vert.xyz;\n"
		"temp.w = 1;\n"
		"gl_Position = u_transform * temp;\n"
		"}\n";

	const char fragSource[] =
		"#version 140\n"
		"#extension GL_ARB_explicit_attrib_location : enable\n"
		"layout(location=0)out vec4 o_color;\n"
		"void main() {\n"
		"o_color = vec4(1,0,1,1);\n"
		"}\n";

	ShaderDef errorShaderDef;
	errorShaderDef.vert = vertSource;
	errorShaderDef.vertSize = sizeof(vertSource);
	errorShaderDef.frag = fragSource;
	errorShaderDef.fragSize = sizeof(fragSource);

	bool result = CreateInternal(errorShaderDef, globals);
	assert(result); // Failed to create error shader
	return true;
}

bool GLShader::CreateInternal(const ShaderDef& source, GLShaderGlobals& globals)
{
	m_vert = CreateSubShader(GL_VERTEX_SHADER, source.vertSize, source.vert);

	if (m_vert == 0)
		return false;

	m_frag = CreateSubShader(GL_FRAGMENT_SHADER, source.fragSize, source.frag);

	if (m_frag == 0)
		return false;

	m_program = glCreateProgram();
	glAttachShader(m_program, m_vert);
	glAttachShader(m_program, m_frag);
	glLinkProgram(m_program);

	GLint linkStatus;
	glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE)
	{
		glDeleteProgram(m_program);
		m_program = 0;

		glDeleteShader(m_vert);
		m_vert = 0;

		glDeleteShader(m_frag);
		m_frag = 0;
		return false;
	}

	// Possibly not effective, binding shader once to give GL chance to internally compile it
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
        
        Uniform uniform;
        uniform.name = (char*)malloc(nameLength+1);
        memcpy(uniform.name, name, nameLength+1);
        
        uniform.location = glGetUniformLocation(m_program, name);
        uniform.globalID = globals.AddProperty(name);
        m_parameters.push_back(uniform);
	}
    
	return true;
}

GLuint GLShader::GetNativeHandle()
{
	return m_program;
}

const GLShader::Uniform* GLShader::Uniforms() const
{
    return m_parameters.data();
}

size_t GLShader::NumUniforms() const
{
    return m_parameters.size();
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

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}
