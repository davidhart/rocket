#include "windows/windowsgamemodule.h"

#if defined(_WIN32)

#include <cassert>

using namespace Rocket;
using namespace Rocket::Windows;

WindowsGameModule::WindowsGameModule() :
	m_module(0),
	m_createproc(nullptr),
	m_releaseproc(nullptr)
{

}

WindowsGameModule::~WindowsGameModule()
{
	if (m_module)
		FreeLibrary(m_module);
}

bool WindowsGameModule::Create(const char* name)
{
	m_module = LoadLibrary(name);
	assert(m_module); // Module not found

	if (m_module == NULL)
		return false;

	m_createproc = (GameModuleCreateProc)GetProcAddress(m_module, "CreateGame");
	assert(m_createproc); // CreateGame not found
	m_releaseproc = (GameModuleReleaseProc)GetProcAddress(m_module, "ReleaseGame");
	assert(m_releaseproc); // ReleaseGame not found

	return (m_createproc != nullptr) && (m_releaseproc != nullptr);
}

Game* WindowsGameModule::CreateGame(Renderer* renderer)
{
	return m_createproc(renderer);
}

void WindowsGameModule::ReleaseGame(Game* game)
{
	m_releaseproc(game);
}

#endif
