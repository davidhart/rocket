#include "opengl/gltexture.h"

#include <cassert>

using namespace Rocket;
using namespace Rocket::OpenGL;


GLTexture1D::GLTexture1D() :
    m_texture(0)
{
}

GLTexture1D::~GLTexture1D()
{
    glDeleteTextures(1, &m_texture);
}

bool GLTexture1D::Create(const TextureDef1D& textureData)
{
    glGenTextures(1, &m_texture);
    assert(m_texture);
    
    GLsizei w = (GLsizei)textureData.width;
    
    glBindTexture(GL_TEXTURE_1D, m_texture);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, w, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.data);
    glGenerateMipmap(GL_TEXTURE_1D);
    
    return true;
}

GLint GLTexture1D::GetNativeHandle()
{
    return m_texture;
}



GLTexture2D::GLTexture2D() :
	m_texture(0)
{
}

GLTexture2D::~GLTexture2D()
{
	glDeleteTextures(1, &m_texture);
}

bool GLTexture2D::Create(const TextureDef2D& textureData)
{
	glGenTextures(1, &m_texture);
	assert(m_texture);

	GLsizei w = (GLsizei)textureData.width;
	GLsizei h = (GLsizei)textureData.height;

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.data);
    glGenerateMipmap(GL_TEXTURE_2D);

	return true;
}

GLint GLTexture2D::GetNativeHandle()
{
	return m_texture;
}



GLTexture3D::GLTexture3D() :
m_texture(0)
{
}

GLTexture3D::~GLTexture3D()
{
    glDeleteTextures(1, &m_texture);
}

bool GLTexture3D::Create(const TextureDef3D& textureData)
{
    glGenTextures(1, &m_texture);
    assert(m_texture);
    
    GLsizei w = (GLsizei)textureData.width;
    GLsizei h = (GLsizei)textureData.height;
    GLsizei d = (GLsizei)textureData.depth;
    
    glBindTexture(GL_TEXTURE_3D, m_texture);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, w, h, d, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.data);
    glGenerateMipmap(GL_TEXTURE_3D);
    
    return true;
}

GLint GLTexture3D::GetNativeHandle()
{
    return m_texture;
}

