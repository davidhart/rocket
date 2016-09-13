#pragma once
#ifndef ROCKET_OPENGL_H
#define ROCKET_OPENGL_H

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
		};
	}
}

#endif