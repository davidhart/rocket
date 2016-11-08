#pragma once
#ifndef ROCKET_WINDOWSKEYBOARD_H
#define ROCKET_WINDOWSKEYBOARD_H

#if defined(_WIN32)

#include "implementation/runtimecontrols.h"
#include <functional>
#include <vector>

namespace Rocket
{
    namespace Windows
    {
        class WindowsKeyboard
        {
        public:
            WindowsKeyboard(Implementation::RuntimeControls* controls, Implementation::ControlScheme* scheme);
            const Implementation::RuntimeControls* ActiveControls() const;

            static void ButtonDown(Implementation::Button* button);
            static void ButtonUp(Implementation::Button* button);

            static void AxisUp(Implementation::Axis* axis, Implementation::KeyboardAxisProvider* provider, bool pressed);
            static void AxisDown(Implementation::Axis* axis, Implementation::KeyboardAxisProvider* provider, bool pressed);

            void KeyDown(int nativeCode);
            void KeyUp(int nativeCode);
            
        private:
            const Implementation::RuntimeControls* m_controls;
            std::map<int, std::function<void()>> m_keyDown;
            std::map<int, std::function<void()>> m_keyUp;

            std::vector<Implementation::KeyboardAxisProvider> m_keyboardAxis;
        };
    }
}

#endif

#endif