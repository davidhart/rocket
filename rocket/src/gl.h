#pragma once

#ifndef ROCKET_GL_INCLUDED
#define ROCKET_GL_INCLUDED

// TODO: safe way to include gl/gl.h
#include <Windows.h>
#include <gl/GL.h>
#include "glcorearb.h"

namespace Rocket
{
	class GL
	{
	public:
		typedef void*(*GetProcImpl)(const char*);
		GL(GetProcImpl get);

#include "generated/gldecl.inl"
	};
}

#endif