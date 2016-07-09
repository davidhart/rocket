#pragma once

#include "igameviewimpl.h"

class WindowsGameViewImpl : public IGameViewImpl
{
public:
	virtual bool Create();
	virtual void SetTitle(const char* title);

private:

};