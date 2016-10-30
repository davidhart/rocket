#pragma once
#ifndef ROCKET_INCLUDED_GAMEVIEW
#define ROCKET_INCLUDED_GAMEVIEW

#include "api.h"
#include "vectormath.h"

namespace Rocket
{
	class Renderer;
    namespace Input
    {
        class IPressAction;
    }

	class IGameViewSizeObserver
	{
	public:
		virtual void GameViewResized(const ivec2& size) = 0;
	};

    class IKey
    {

    };

    enum KeyCode
    {
        KEY_SPACE
    };

	class GameView
	{
	public:
		
		ROCKET_API static GameView* Create(const char* title);
		ROCKET_API static void Release(GameView* view);
		virtual ~GameView();

		virtual Renderer* CreateRenderer() = 0;
		virtual void ReleaseRenderer(Renderer* renderer) = 0;

		virtual void SetTitle(const char* title) = 0;

		virtual void SetIsResizable(bool isResizable) = 0;
		virtual bool GetIsResizable() = 0;

		virtual void Update(float delta) = 0;
		virtual bool IsClosed() = 0;

		virtual void AddSizeObserver(IGameViewSizeObserver* observer) = 0;
		virtual void RemoveSizeObserver(IGameViewSizeObserver* observer) = 0;

        virtual Input::IPressAction* AddPressAction(const char* name) = 0;
        virtual Input::IPressAction* GetPressAction(const char* name) = 0;
        virtual void RemovePressAction(const char* name) = 0;

        virtual void SetKeyboardMapping(const char* name, IKey* key) = 0;
        virtual IKey* GetKey(KeyCode code) = 0;
	};

}

#endif