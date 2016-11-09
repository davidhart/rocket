#pragma once
#ifndef ROCKET_RUNTIMECONTROLS_INCLUDED
#define ROCKET_RUNTIMECONTROLS_INCLUDED

#include "input.h"
#include <map>
#include <string>

namespace Rocket
{
    namespace Implementation
    {
        class ControlScheme;

        class Button final : public Input::IButton
        {
        public:
            Button();
            virtual bool IsPressed();
            virtual bool WasJustPressed();
            virtual bool WasJustReleased();

            void Update();
            void OnButtonDown();
            void OnButtonUp();

        private:
            bool m_isPressed;
            bool m_wasPressed;
            bool m_wasReleased;
        };

        class IAxisProvider
        {
        public:
            virtual float Value() = 0;
        };

        class Axis final : public Input::IAxis
        {
        public:
            Axis();
            virtual float Value();
            void SetProvider(IAxisProvider* provider);

        private:
            IAxisProvider* m_provider;
        };

        class RuntimeControls final : public Input::IRuntimeControls
        {
        public:
            RuntimeControls(ControlScheme* scheme);
            ~RuntimeControls();
            virtual Input::IButton* GetButton(const char* name);
            virtual Input::IAxis* GetAxis(const char* name);

            void Update(float dt);
            Button* GetButtonInternal(const char* name);
            Axis* GetAxisInternal(const char* name);

        private:
            std::map<std::string, Button*> m_buttons;
            std::map<std::string, Axis*> m_axis;
        };

        class KeyboardAxisProvider final : public IAxisProvider
        {
        public:
            KeyboardAxisProvider();
            virtual float Value();
            void SetUpKeyState(bool pressed);
            void SetDownKeyState(bool pressed);

        private:
            bool m_upKey;
            bool m_downKey;
        };
    }
}

#endif
