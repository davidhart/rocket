#pragma once
#ifndef ROCKET_BASEGAMEVIEW_INCLUDED
#define ROCKET_BASEGAMEVIEW_INCLUDED

#include "gameview.h"
#include "input.h"
#include "implementation/runtimekeyboard.h"
#include <vector>
#include <map>
#include <string>

namespace Rocket
{
	namespace Implementation
	{
        class ControlScheme;
        class RuntimeControls;
        class RuntimeKeyboard;

		class BaseGameView : public GameView, public IRuntimeKeyboardTranslator
		{
		public:
            virtual ~BaseGameView();
            virtual void Update(float delta);

			virtual void AddSizeObserver(IGameViewSizeObserver* observer);
			virtual void RemoveSizeObserver(IGameViewSizeObserver* observer);
			virtual void NotifySizeObservers(const ivec2& size);


            virtual Input::IControlScheme* AddControlScheme(const char* name);
            virtual Input::IControlScheme* GetControlScheme(const char* name);
            virtual void RemoveControlScheme(const char* name);

            virtual Input::IRuntimeControls* ActivateControlScheme(const char* name);
            virtual Input::IRuntimeControls* GetActiveControlScheme(const char* name);
            virtual void DeactivateControlScheme(const char* name);
            
            virtual int TranslateKeyCodeToNative(Input::KeyCode code) = 0;
            
            void NativeKeyDown(int key);
            void NativeKeyUp(int key);

		private:
            std::vector<IGameViewSizeObserver*> m_sizeObservers;

            std::map<std::string, ControlScheme*> m_controlSchemes;
            std::map<std::string, RuntimeControls*> m_runtimeControls;
            std::vector<RuntimeKeyboard*> m_keyboards;
		};
	}
}

#endif
