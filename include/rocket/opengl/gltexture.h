#pragma once
#ifndef ROCKET_INCLUDED_GLTEXTURE
#define ROCKET_INCLUDED_GLTEXTURE

#include "rocket_opengl.h"
#include "../texture.h"

namespace Rocket
{
	namespace OpenGL
	{
        class GLTexture1D : public Texture1D
        {
        public:
            GLTexture1D();
            ~GLTexture1D();
            
            bool Create(const TextureDef1D& data);
            GLint GetNativeHandle();
            
        private:
            GLuint m_texture;
        };
        
        class GLTexture2D : public Texture2D
        {
        public:
            GLTexture2D();
            ~GLTexture2D();
            
            bool Create(const TextureDef2D& data);
            GLint GetNativeHandle();
            
        private:
            GLuint m_texture;
        };
        
		class GLTexture3D : public Texture3D
		{
		public:
			GLTexture3D();
			~GLTexture3D();

			bool Create(const TextureDef3D& data);
			GLint GetNativeHandle();

		private:
			GLuint m_texture;
		};
	}
}

#endif
