#include "texture.h"

#include <cassert>

using namespace Rocket;

TextureSamplerDef1D::TextureSamplerDef1D() :
	widthWrap(WRAP_CLAMP_TO_EDGE),
	minFilter(MIN_NEAREST),
	magFilter(MAG_NEAREST)
{
}

TextureSamplerDef2D::TextureSamplerDef2D() :
	widthWrap(WRAP_CLAMP_TO_EDGE),
	heightWrap(WRAP_CLAMP_TO_EDGE),
	minFilter(MIN_NEAREST),
	magFilter(MAG_NEAREST)
{
}

TextureSamplerDef3D::TextureSamplerDef3D() :
	widthWrap(WRAP_CLAMP_TO_EDGE),
	heightWrap(WRAP_CLAMP_TO_EDGE),
	depthWrap(WRAP_CLAMP_TO_EDGE),
	minFilter(MIN_NEAREST),
	magFilter(MAG_NEAREST)
{
}

unsigned Texture::PixelSizeForFormat(TextureFormat format)
{
	switch (format)
	{
	case TEXFMT_RGBA_32:
		return 4;
	case TEXFMT_RGB_24:
		return 3;
	case TEXFMT_FLOAT_16:
		return 2;
	case TEXFMT_FLOAT_32:
		return 4;
	case TEXFMT_DEPTH_16:
		return 2;
	case TEXFMT_DEPTH_32:
		return 4;
	default:
		assert(false); // Unsupported texture format
	}

	return 0;
}

Texture::Texture()
{

}

Texture::~Texture()
{

}