#pragma once
#ifndef ROCKET_INCLUDED_TEXTURE
#define ROCKET_INCLUDED_TEXTURE

namespace Rocket
{
	// TODO: support:
	// texture 1d array, 2d array
	// non u8 rgba pixel formats
	enum TextureType
	{
		TEXTURE_1D,
		TEXTURE_2D,
		TEXTURE_3D
	};

	struct TextureDef
	{
		TextureType type;

		unsigned width;
		unsigned height;
		unsigned depth;
		
		const void* data;
		unsigned size;
	};

	class Texture
	{
	protected:
		Texture();

	public:
		virtual ~Texture();

	private:
		Texture(const Texture& texture);
	};
}

#endif
