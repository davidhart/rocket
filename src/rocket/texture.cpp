#include "texture.h"

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

Texture::Texture()
{

}

Texture::~Texture()
{

}