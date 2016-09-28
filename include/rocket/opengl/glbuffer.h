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

			bool Create(unsigned size, void* data);

			virtual void UpdateData(void* data, unsigned size, unsigned offset = 0);
			virtual unsigned Size() const;
			
			virtual void* Map(MapUsage usage);
			virtual void Unmap();

			GLuint GetNativeHandle();

		private:
			GLuint m_handle;
			unsigned m_size;
		};
	}
}

#endif
