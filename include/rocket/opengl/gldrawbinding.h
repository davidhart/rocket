#pragma once
#ifndef ROCKET_GLDRAWBINDING_INCLUDED
#define ROCKET_GLDRAWBINDING_INCLUDED

#include "../drawbinding.h"
#include "rocket_opengl.h"

namespace Rocket
{
	namespace OpenGL
	{
		class GLDrawBinding : public DrawBinding
		{
		public:
			GLDrawBinding();
			~GLDrawBinding();
			bool Create(const DrawBindingDef& drawBindingDef);

			void Draw();

		private:
			GLDrawBinding(const GLDrawBinding&);

			bool m_useIndexBuffer;
			GLsizei m_numElements;
			GLenum m_indexType;
			unsigned m_indexOffset;
			GLuint m_vao;
		};
	}
}

#endif
