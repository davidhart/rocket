#pragma once
#ifndef ROCKET_INPUT_INCLUDED
#define ROCKET_INPUT_INCLUDED

namespace Rocket
{
    namespace Input
    {
        enum KeyCode
        {
            KEY_A,
            KEY_B,
            KEY_C,
            KEY_D,
            KEY_E,
            KEY_F,
            KEY_G,
            KEY_H,
            KEY_I,
            KEY_J,
            KEY_K,
            KEY_L,
            KEY_M,
            KEY_N,
            KEY_O,
            KEY_P,
            KEY_Q,
            KEY_R,
            KEY_S,
            KEY_T,
            KEY_U,
            KEY_V,
            KEY_W,
            KEY_X,
            KEY_Y,
            KEY_Z,
            KEY_0,
            KEY_1,
            KEY_2,
            KEY_3,
            KEY_4,
            KEY_5,
            KEY_6,
            KEY_7,
            KEY_8,
            KEY_9,
            KEY_SPACE
        };

        class IButton
        {
        public:
            virtual bool IsPressed() = 0;
            virtual bool WasJustPressed() = 0;
            virtual bool WasJustReleased() = 0;
        };

        class IAxis
        {
        public:
            virtual float Value() = 0;
        };

        class IRuntimeControls
        {
        public:
            virtual IButton* GetButton(const char* name) = 0;
            virtual IAxis* GetAxis(const char* name) = 0;
        };

        class IControlScheme
        {
        public:
            virtual const char* Name() const = 0;
            virtual void AddButton(const char* name) = 0;
            virtual void AddAxis(const char* name) = 0;
            
            virtual void AddButtonKeyboardMapping(const char* name, KeyCode keycode) = 0;
            virtual void AddAxisKeyboardMapping(const char* name, KeyCode down, KeyCode up) = 0;
        };

    }
}

#endif
