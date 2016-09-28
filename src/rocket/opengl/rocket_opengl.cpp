#include "opengl/rocket_opengl.h"
#include <cassert>

static bool s_isInitialized = false;

namespace Rocket
{
	namespace OpenGL
	{
#include "opengl/generated/gldefn.h"

		bool Platform::IsInitialized()
		{
			return s_isInitialized;
		}

		void Platform::Initialize(GetProcImpl get)
		{
#include "opengl/generated/glsetup.h"
			s_isInitialized = true;
		}
	}
}
