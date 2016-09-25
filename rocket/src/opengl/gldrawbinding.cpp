#include "gldrawbinding.h"
#include <cassert>

using namespace Rocket;
using namespace Rocket::OpenGL;

GLDrawBinding::GLDrawBinding() :
	m_vao(0)
{
}

GLDrawBinding::~GLDrawBinding()
{

}

bool GLDrawBinding::Create(const DrawBindingDef& drawBindingDef)
{
	glGenVertexArrays(1, &m_vao);
	assert(m_vao);
	
	glBindVertexArray(m_vao);

	// Setup the vertex array

	glBindVertexArray(0);

	return true;
}