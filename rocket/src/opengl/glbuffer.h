#pragma once
#ifndef ROCKET_INCLUDED_GLVERTEXBUFFER
#define ROCKET_INCLUDED_GLVERTEXBUFFER

#include "../buffer.h"
#include "rocket_opengl.h"

namespace Rocket
{
	namespace OpenGL
	{
		class GLBuffer : public Buffer
		{
		public:
			GLBuffer();
			virtual ~GLBuffer();

			bool Create(size_t size, void* data);

			virtual void UpdateData(void* data, size_t size, size_t offset = 0);
			virtual size_t Size() const;
			
			virtual void* Map(MapUsage usage);
			virtual void Unmap();

		private:
			GLuint m_handle;
			size_t m_size;
		};
	}
}

#endif