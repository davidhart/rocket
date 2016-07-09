#pragma once

class IGameViewImpl
{
public:
	virtual bool Create() = 0;
	virtual void SetTitle(const char* title) = 0;
};