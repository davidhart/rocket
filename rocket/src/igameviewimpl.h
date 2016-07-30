#pragma once

class IGameViewImpl
{
public:
	virtual ~IGameViewImpl() { };
	virtual bool Create() = 0;
	virtual void SetTitle(const wchar_t* title) = 0;
	virtual void FlushEvents() = 0;
	virtual bool IsClosed() = 0;
};