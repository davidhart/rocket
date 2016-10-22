#include "opengl/gltexture.h"

#include <cassert>

using namespace Rocket;
using namespace Rocket::OpenGL;

GLenum WrapModeToGLEnum(WrapMode wrap)
{
	switch (wrap)
	{
	case WRAP_CLAMP_TO_EDGE:
		return GL_CLAMP_TO_EDGE;

	case WRAP_REPEAT:
		return GL_REPEAT;

	default:
		assert(false); // Unsupported wrap mode
	}
	
	return 0;
}

GLenum MinFilterToGLEnum(MinFilter filter)
{
	switch (filter)
	{
	case MIN_NEAREST:
		return GL_NEAREST;

	case MIN_LINEAR:
		return GL_LINEAR;

	case MIN_NEAREST_MIP_NEAREST:
		return GL_NEAREST_MIPMAP_NEAREST;

	case MIN_NEAREST_MIP_LINEAR:
		return GL_NEAREST_MIPMAP_LINEAR;
		
	case MIN_LINEAR_MIP_NEAREST:
		return GL_LINEAR_MIPMAP_NEAREST;

	case MIN_LINEAR_MIP_LINEAR:
		return GL_LINEAR_MIPMAP_LINEAR;

	default:
		assert(false); // Unsupported min filter
	}

	return 0;
}

GLenum MagFilterToGLEnum(MagFilter filter)
{
	switch (filter)
	{
	case MAG_LINEAR:
		return GL_LINEAR;

	case MAG_NEAREST:
		return GL_NEAREST;

	default:
		assert(false); // Unsupported mag filter
	}

	return 0;
}

GLenum FormatToInternalFormat(TextureFormat format)
{
	switch (format)
	{
	case TEXFMT_RGBA_32:
		return GL_RGBA;

	case TEXFMT_RGB_24:
		return GL_RGB;

	case TEXFMT_FLOAT_16:
		return GL_R16F;

	case TEXFMT_FLOAT_32:
		return GL_R32F;

	case TEXFMT_DEPTH_16:
		return GL_DEPTH_COMPONENT;

	case TEXFMT_DEPTH_32:
		return GL_DEPTH_COMPONENT;

	default:
		assert(false); // Unsupported format
	}

	return 0;
}

GLenum FormatToGLFormat(TextureFormat format)
{
	switch (format)
	{
	case TEXFMT_RGBA_32:
		return GL_RGBA;

	case TEXFMT_RGB_24:
		return GL_RGB;

	case TEXFMT_FLOAT_16:
		return GL_RED;

	case TEXFMT_FLOAT_32:
		return GL_RED;

	case TEXFMT_DEPTH_16:
		return GL_DEPTH_COMPONENT;

	case TEXFMT_DEPTH_32:
		return GL_DEPTH_COMPONENT;
		
	default:
		assert(false); // Unsupported format
	}

	return 0;
}

GLenum FormatToDataType(TextureFormat format)
{
	switch (format)
	{
	case TEXFMT_RGBA_32:
		return GL_UNSIGNED_BYTE;

	case TEXFMT_RGB_24:
		return GL_UNSIGNED_BYTE;

	case TEXFMT_FLOAT_16:
		return GL_FLOAT;

	case TEXFMT_FLOAT_32:
		return GL_FLOAT;

	case TEXFMT_DEPTH_16:
		return GL_UNSIGNED_SHORT;

	case TEXFMT_DEPTH_32:
		return GL_UNSIGNED_INT;

	default:
		assert(false); // Unsupported format
	}

	return 0;
}

void ApplyMinMagSettings(GLenum target, MinFilter minFilter, MagFilter magFilter)
{
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, MinFilterToGLEnum(minFilter));
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, MagFilterToGLEnum(magFilter));

	// If mipmaps are required then generate mipmaps
	// TODO: Support supplying pre-generated mipmaps
	if (minFilter == MIN_NEAREST_MIP_NEAREST || 
		minFilter == MIN_NEAREST_MIP_LINEAR || 
		minFilter == MIN_LINEAR_MIP_LINEAR || 
		minFilter == MIN_LINEAR_MIP_LINEAR)
	{
		glGenerateMipmap(target);
	}
}

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
    
	GLenum internal = FormatToInternalFormat(textureData.format);
	GLenum format = FormatToGLFormat(textureData.format);
	GLenum type = FormatToDataType(textureData.format);

	assert(w*Texture::PixelSizeForFormat(textureData.format) == textureData.size); // Size mismatch

    glBindTexture(GL_TEXTURE_1D, m_texture);
    glTexImage1D(GL_TEXTURE_1D, 0, internal, w, 0, format, type, textureData.data);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_R, WrapModeToGLEnum(textureData.sampler.widthWrap));
	ApplyMinMagSettings(GL_TEXTURE_1D, textureData.sampler.minFilter, textureData.sampler.magFilter);

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

	GLenum internal = FormatToInternalFormat(textureData.format);
	GLenum format = FormatToGLFormat(textureData.format);
	GLenum type = FormatToDataType(textureData.format);

	assert(w * h * Texture::PixelSizeForFormat(textureData.format) == textureData.size); // Size mismatch

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, internal, w, h, 0, format, type, textureData.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, WrapModeToGLEnum(textureData.sampler.widthWrap));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapModeToGLEnum(textureData.sampler.heightWrap));
	ApplyMinMagSettings(GL_TEXTURE_2D, textureData.sampler.minFilter, textureData.sampler.magFilter);

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

	GLenum internal = FormatToInternalFormat(textureData.format);
	GLenum format = FormatToGLFormat(textureData.format);
	GLenum type = FormatToDataType(textureData.format);
    
	assert(w*h*d*Texture::PixelSizeForFormat(textureData.format) == textureData.size); // Size mismatch

    glBindTexture(GL_TEXTURE_3D, m_texture);
    glTexImage3D(GL_TEXTURE_3D, 0, internal, w, h, d, 0, format, type, textureData.data);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, WrapModeToGLEnum(textureData.sampler.widthWrap));
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, WrapModeToGLEnum(textureData.sampler.heightWrap));
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, WrapModeToGLEnum(textureData.sampler.depthWrap));
	ApplyMinMagSettings(GL_TEXTURE_3D, textureData.sampler.minFilter, textureData.sampler.magFilter);

    return true;
}

GLint GLTexture3D::GetNativeHandle()
{
    return m_texture;
}

