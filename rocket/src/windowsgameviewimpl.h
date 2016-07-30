#pragma once

#include "igameviewimpl.h"

#include <Windows.h>

class WindowsGameViewImpl : public IGameViewImpl
{
public:
	WindowsGameViewImpl();
	virtual ~WindowsGameViewImpl();
	virtual bool Create();
	virtual void SetTitle(const wchar_t* title);
	virtual void FlushEvents();
	virtual bool IsClosed();
	LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

private:

	bool isClassRegistered;
	HWND hwnd;
	bool isWindowClosed;
};