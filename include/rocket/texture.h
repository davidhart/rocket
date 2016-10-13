#pragma once
#ifndef ROCKET_INCLUDED_TEXTURE
#define ROCKET_INCLUDED_TEXTURE

namespace Rocket
{
	// TODO: support:
	// texture 1d array, 2d array
	// non u8 rgba pixel formats
    
    struct TextureDef1D
    {
        unsigned width;
        
        const void* data;
        unsigned size;
    };

	struct TextureDef2D
	{
		unsigned width;
		unsigned height;
		
		const void* data;
		unsigned size;
	};
    
    struct TextureDef3D
    {
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
		Texture(const Texture&);
	};
    
    class Texture1D : public Texture
    {
    };
    
    class Texture2D : public Texture
    {
    };
    
    class Texture3D : public Texture
    {
    };
}

#endif
