#include "gl.h"
#include <cassert>

using namespace Rocket;

GL::GL(GL::GetProcImpl get)
{
#include "generated/glsetup.inl"
}