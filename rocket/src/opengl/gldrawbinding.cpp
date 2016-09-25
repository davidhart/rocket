#include "gldrawbinding.h"
#include "glbuffer.h"

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

	for (int i = 0; i < drawBindingDef.numVertexAttributes; ++i)
	{
		VertexBinding* binding = drawBindingDef.vertexAttributes + i;
		GLuint bufferHandle = ((GLBuffer*)binding->buffer)->GetNativeHandle();

		GLuint attribIndex = (GLuint)binding->index;
		GLint size = (GLuint)binding->components;
		GLsizei stride = (GLsizei)binding->stride;
		void* offset = (void*)binding->offset;

		glEnableVertexAttribArray(attribIndex);
		glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);

		switch (binding->type)
		{
		case DB_TYPE_DOUBLE:
			glVertexAttribPointer(attribIndex, size, GL_DOUBLE, GL_FALSE, stride, offset);
			break;

		case DB_TYPE_FLOAT:
			glVertexAttribPointer(attribIndex, size, GL_FLOAT, GL_FALSE, stride, offset);
			break;
			
		case DB_TYPE_INT8:
			glVertexAttribIPointer(attribIndex, size, GL_BYTE, stride, offset);
			break;

		case DB_TYPE_UINT8:
			glVertexAttribIPointer(attribIndex, size, GL_UNSIGNED_BYTE, stride, offset);
			break;

		case DB_TYPE_INT16:
			glVertexAttribIPointer(attribIndex, size, GL_SHORT, stride, offset);
			break;

		case DB_TYPE_UINT16:
			glVertexAttribIPointer(attribIndex, size, GL_UNSIGNED_SHORT, stride, offset);
			break;

		case DB_TYPE_INT32:
			glVertexAttribIPointer(attribIndex, size, GL_INT, stride, offset);
			break;

		case DB_TYPE_UINT32:
			glVertexAttribIPointer(attribIndex, size, GL_UNSIGNED_INT, stride, offset);
			break;

		default:
			assert(false); // Binding type not implemented
		}
	}

	if (drawBindingDef.indexAttributes != nullptr)
	{
		glEnable(GL_ELEMENT_ARRAY_BUFFER);
		GLuint indexBufferHandle = ((GLBuffer*)drawBindingDef.indexAttributes->buffer)->GetNativeHandle();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	}

	glBindVertexArray(0);

	m_def = drawBindingDef;

	return true;
}

GLuint GLDrawBinding::GetNativeHandle()
{
	return m_vao;
}

size_t GLDrawBinding::GetNumElements()
{
	return m_def.length;
}