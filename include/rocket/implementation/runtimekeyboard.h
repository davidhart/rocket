#pragma once
#ifndef ROCKET_RUNTIMEKEYBOARD_H
#define ROCKET_RUNTIMEKEYBOARD_H

#include "implementation/runtimecontrols.h"
#include "input.h"
#include <functional>
#include <vector>

namespace Rocket
{
    namespace Implementation
    {
        class IRuntimeKeyboardTranslator
        {
        public:
            virtual int TranslateKeyCodeToNative(Input::KeyCode code) = 0;
        };
        
        class RuntimeKeyboard
        {
        public:
            RuntimeKeyboard(RuntimeControls* controls, ControlScheme* scheme, IRuntimeKeyboardTranslator* translator);
            const RuntimeControls* ActiveControls() const;

            static void ButtonDown(Button* button);
            static void ButtonUp(Button* button);

            static void AxisUp(Axis* axis, KeyboardAxisProvider* provider, bool pressed);
            static void AxisDown(Axis* axis, KeyboardAxisProvider* provider, bool pressed);
            
            void KeyDown(int nativeCode);
            void KeyUp(int nativeCode);
            
        private:
            const RuntimeControls* m_controls;
            std::map<int, std::function<void()>> m_keyDown;
            std::map<int, std::function<void()>> m_keyUp;

            std::vector<KeyboardAxisProvider> m_keyboardAxis;
        };
    }
}

#endif
