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

			GLuint GetNativeHandle();
			unsigned GetNumElements();

		private:
			GLDrawBinding(const GLDrawBinding&);

			DrawBindingDef m_def;
			GLuint m_vao;
		};
	}
}

#endif
