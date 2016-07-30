#pragma once

class IGameViewImpl;

class GameView
{
public:
	static GameView* Create(const wchar_t* title);
	static void Release(GameView* view);

	void SetTitle(const wchar_t* title);

	void FlushEvents();
	bool IsClosed();

private:
	GameView(IGameViewImpl* impl);
	GameView(const GameView& view);
	~GameView();

	IGameViewImpl* impl;
};

