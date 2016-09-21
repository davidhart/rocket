#pragma once
#ifndef ROCKET_INCLUDED_OPENGL
#define ROCKET_INCLUDED_OPENGL

#if _WIN32
#include <Windows.h>
#endif

#include <gl/GL.h>
#include "glcorearb.h"

namespace Rocket
{
	namespace OpenGL
	{
#include "generated/gldecl.inl"

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