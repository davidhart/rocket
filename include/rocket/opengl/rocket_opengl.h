#pragma once
#ifndef ROCKET_INCLUDED_OPENGL
#define ROCKET_INCLUDED_OPENGL

#if _WIN32
#include <Windows.h>
#include <gl/GL.h>

#elif __APPLE__
#include <OpenGL/GL.h>
#endif

#if defined(GL_VERSION_1_2)
#define ROCKET_GL_1_2_LINKED 1
#endif

#if defined(GL_VERSION_1_3)
#define ROCKET_GL_1_3_LINKED 1
#endif

#if defined(GL_VERSION_1_4)
#define ROCKET_GL_1_4_LINKED 1
#endif

#if defined(GL_VERSION_1_5)
#define ROCKET_GL_1_5_LINKED 1
#endif

#if defined(GL_VERSION_2_0)
#define ROCKET_GL_2_0_LINKED 1
#endif

#if defined(GL_VERSION_2_1)
#define ROCKET_GL_2_1_LINKED 1
#endif

#if defined(GL_VERSION_3_0)
#define ROCKET_GL_3_0_LINKED 1
#endif

#include "glcorearb.h"

namespace Rocket
{
	namespace OpenGL
	{
#include "generated/gldecl.h"

		class Platform
		{
		public:
			typedef void*(*GetProcImpl)(const char*);

			static bool IsInitialized();
			static void Initialize(GetProcImpl get);

		private:
			Platform();
			Platform(const Platform&);
			~Platform();
		};
	}
}

#endif
