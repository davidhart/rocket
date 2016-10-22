#pragma once
#ifndef ROCKET_INCLUDED_TEXTURE
#define ROCKET_INCLUDED_TEXTURE

namespace Rocket
{
	// TODO: support:
	// texture 1d array, 2d array
	// non u8 rgba pixel formats
    
	enum TextureFormat
	{
		TEXFMT_RGBA_32,
		TEXFMT_RGB_24,
		TEXFMT_FLOAT_16,
		TEXFMT_FLOAT_32,
		TEXFMT_DEPTH_16,
		TEXFMT_DEPTH_32,
	};

	enum WrapMode
	{
		WRAP_CLAMP_TO_EDGE,
		WRAP_REPEAT,
	};

	enum MagFilter
	{
		MAG_NEAREST,
		MAG_LINEAR
	};

	enum MinFilter
	{
		MIN_NEAREST,
		MIN_LINEAR,
		MIN_NEAREST_MIP_NEAREST,
		MIN_NEAREST_MIP_LINEAR,
		MIN_LINEAR_MIP_NEAREST,
		MIN_LINEAR_MIP_LINEAR
	};

	struct TextureSamplerDef1D
	{
		WrapMode widthWrap;
		MinFilter minFilter;
		MagFilter magFilter;

		TextureSamplerDef1D();
	};

    struct TextureDef1D
    {
        unsigned width;
		TextureFormat format;
		TextureSamplerDef1D sampler;
        
        const void* data;
        unsigned size;
    };

	struct TextureSamplerDef2D
	{
		WrapMode widthWrap;
		WrapMode heightWrap;
        MinFilter minFilter;
		MagFilter magFilter;

		TextureSamplerDef2D();
	};

	struct TextureDef2D
	{
		unsigned width;
		unsigned height;
		TextureFormat format;
		TextureSamplerDef2D sampler;
		
		const void* data;
		unsigned size;
	};

	struct TextureSamplerDef3D
	{
		WrapMode widthWrap;
		WrapMode heightWrap;
		WrapMode depthWrap;
        MinFilter minFilter;
		MagFilter magFilter;

		TextureSamplerDef3D();
	};
    
    struct TextureDef3D
    {
        unsigned width;
        unsigned height;
        unsigned depth;
		TextureFormat format;
		TextureSamplerDef3D sampler;
        
        const void* data;
        unsigned size;
    };

	class Texture
	{
	protected:
		Texture();


	public:
		virtual ~Texture();

		static unsigned PixelSizeForFormat(TextureFormat format);

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
