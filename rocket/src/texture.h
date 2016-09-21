#pragma once
#ifndef ROCKET_INCLUDED_TEXTURE
#define ROCKET_INCLUDED_TEXTURE

namespace Rocket
{
	struct TextureData
	{
		size_t width;
		size_t height;
		
		void* data;
		size_t size;
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