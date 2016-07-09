#pragma once

class IGameViewImpl;

class GameView
{
public:
	static GameView* Create(const char* title);
	static void Release(GameView* view);

	void SetTitle(const char* title);

private:
	GameView(IGameViewImpl* impl);
	GameView(const GameView& view);
	~GameView();

	IGameViewImpl* impl;
};

