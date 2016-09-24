#include "gltexture.h"

#include <cassert>

using namespace Rocket;
using namespace Rocket::OpenGL;

GLTexture::GLTexture() :
	m_texture(0)
{
}

GLTexture::~GLTexture()
{
	glDeleteTextures(1, &m_texture);
}

bool GLTexture::Create(const TextureData& textureData)
{
	glGenTextures(1, &m_texture);
	assert(m_texture);

	GLsizei w = (GLsizei)textureData.width;
	GLsizei h = (GLsizei)textureData.height;
	GLsizei d = (GLsizei)textureData.depth;

	switch (textureData.type)
	{
	case TEXTURE_1D:
		glBindTexture(GL_TEXTURE_1D, m_texture);
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, w, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.data);
		glGenerateMipmap(GL_TEXTURE_1D);
		break;

	case TEXTURE_2D:
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.data);
		glGenerateMipmap(GL_TEXTURE_2D);
		break;

	case TEXTURE_3D:
		glBindTexture(GL_TEXTURE_3D, m_texture);
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, w, h, d, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.data);
		glGenerateMipmap(GL_TEXTURE_3D);
		break;

	default:
		assert(false);
	}

	return true;
}
