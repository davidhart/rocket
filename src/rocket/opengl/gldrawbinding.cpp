#include "opengl/gldrawbinding.h"
#include "opengl/glbuffer.h"

#include <cassert>

using namespace Rocket;
using namespace Rocket::OpenGL;

GLenum VertexBindingTypeToGLEnum(VertexBindingType type)
{
	switch (type)
	{
	case VB_TYPE_FLOAT:
		return GL_FLOAT;
	case VB_TYPE_DOUBLE:
		return GL_DOUBLE;
	case VB_TYPE_INT8:
		return GL_BYTE;
	case VB_TYPE_UINT8:
		return GL_UNSIGNED_BYTE;
	case VB_TYPE_INT16:
		return GL_SHORT;
	case VB_TYPE_UINT16:
		return GL_UNSIGNED_SHORT;
	case VB_TYPE_INT32:
		return GL_INT;
	case VB_TYPE_UINT32:
		return GL_UNSIGNED_INT;
	default:
		assert(false); // Unsupported VertexBindingType
	}

	return 0;
}

bool IsVertexIntegerType(VertexBindingType type)
{
	switch (type)
	{
	case VB_TYPE_FLOAT:
	case VB_TYPE_DOUBLE:
		return false;

	case VB_TYPE_INT8:
	case VB_TYPE_UINT8:
	case VB_TYPE_INT16:
	case VB_TYPE_UINT16:
	case VB_TYPE_INT32:
	case VB_TYPE_UINT32:
		return true;

	default:
		assert(false); // Unsupported VertexBindingType
	}

	return false;
}

GLenum IndexBindingTypeToGLEnum(IndexBindingType type)
{
	switch (type)
	{
	case IB_TYPE_UINT8:
		return GL_UNSIGNED_BYTE;
	case IB_TYPE_UINT16:
		return GL_UNSIGNED_SHORT;
	case IB_TYPE_UINT32:
		return GL_UNSIGNED_INT;

	default:
		assert(false); // Unsupported IndexBindingType
	}
	
	return 0;
}

GLDrawBinding::GLDrawBinding() :
	m_useIndexBuffer(false),
	m_numElements(0),
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

	for (unsigned i = 0; i < drawBindingDef.numVertexAttributes; ++i)
	{
		VertexBinding* binding = drawBindingDef.vertexAttributes + i;
		GLuint bufferHandle = ((GLBuffer*)binding->buffer)->GetNativeHandle();

		GLuint attribIndex = (GLuint)binding->index;
		GLint size = (GLuint)binding->components;
		GLsizei stride = (GLsizei)binding->stride;
		void* offset = reinterpret_cast<void*>(binding->offset);

		glEnableVertexAttribArray(attribIndex);
		glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);

		GLenum vertType = VertexBindingTypeToGLEnum(binding->type);
		
		if (IsVertexIntegerType(binding->type))
		{
			glVertexAttribIPointer(attribIndex, size, vertType, stride, offset);
		}
		else
		{
			glVertexAttribPointer(attribIndex, size, vertType, GL_FALSE, stride, offset);
		}
	}
    
	m_useIndexBuffer = drawBindingDef.indexAttributes != nullptr;
	
	if (m_useIndexBuffer)
	{
		GLuint indexBufferHandle = ((GLBuffer*)drawBindingDef.indexAttributes->buffer)->GetNativeHandle();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);

		m_useIndexBuffer = true;
		m_indexType = IndexBindingTypeToGLEnum(drawBindingDef.indexAttributes->type);
		m_indexOffset = drawBindingDef.indexAttributes->offet;
	}
	else
	{
		m_useIndexBuffer = false;
	}
	m_numElements = (GLsizei)drawBindingDef.length;

	glBindVertexArray(0);

	return true;
}

void GLDrawBinding::Draw()
{
	glBindVertexArray(m_vao);

	if (m_useIndexBuffer)
	{
		glDrawElements(GL_TRIANGLES, m_numElements, m_indexType, reinterpret_cast<void*>(m_indexOffset));
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, m_numElements);
	}

}
