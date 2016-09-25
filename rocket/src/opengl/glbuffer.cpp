#include "glbuffer.h"
#include <cassert>

using namespace Rocket::OpenGL;


GLBuffer::GLBuffer() :
	m_handle(0),
	m_size(0)
{

}

GLBuffer::~GLBuffer()
{
	if (m_handle != 0)
	{
		glDeleteBuffers(1, &m_handle);
	}
}

bool GLBuffer::Create(size_t size, void* data)
{
	assert(m_handle == 0); // GLVertexBuffer already initialised

	glGenBuffers(1, &m_handle);

	if (glGetError() != GL_NO_ERROR)
		return false;

	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

	if (glGetError() != GL_NO_ERROR)
	{
		glDeleteBuffers(1, &m_handle);
		m_handle = 0;
		return false;
	}

	m_size = size;
	return true;
}

void GLBuffer::UpdateData(void* data, size_t size, size_t offset)
{
	assert(offset + size <= m_size); // GLVertexBuffer update out of range
	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

size_t GLBuffer::Size() const
{
	return m_size;
}

void* GLBuffer::Map(Buffer::MapUsage usage)
{
	GLenum glaccess;

	switch (usage)
	{
	case Buffer::MAP_READ_ONLY:
		glaccess = GL_READ_ONLY;
		break;
	case Buffer::MAP_WRITE_ONLY:
		glaccess = GL_WRITE_ONLY;
		break;
	case Buffer::MAP_READ_AND_WRITE:
		glaccess = GL_READ_WRITE;
	default:
		assert(false); // GLVertexBuffer MapUsage type not implemented
		return nullptr;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	return glMapBuffer(GL_ARRAY_BUFFER, glaccess);
}

void GLBuffer::Unmap()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_handle);
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

GLuint GLBuffer::GetNativeHandle()
{
	return m_handle;
}