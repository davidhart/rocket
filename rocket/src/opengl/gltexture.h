#pragma once
#ifndef ROCKET_INCLUDED_GLTEXTURE
#define ROCKET_INCLUDED_GLTEXTURE

#include "rocket_opengl.h"
#include "../texture.h"

namespace Rocket
{
	namespace OpenGL
	{
		class GLTexture : public Texture
		{
		public:
			GLTexture();
			~GLTexture();

			bool Create(const TextureData& data);

		private:
			GLint m_texture;
		};
	}
}

#endif