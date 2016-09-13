#pragma once

#include "rocket_opengl.h"
#include <cassert>

static bool s_isInitialized = false;

namespace Rocket
{
	namespace OpenGL
	{
#include "generated/gldefn.inl"

		bool Platform::IsInitialized()
		{
			return s_isInitialized;
		}

		void Platform::Initialize(GetProcImpl get)
		{
#include "generated/glsetup.inl"
			s_isInitialized = true;
		}
	}
}
