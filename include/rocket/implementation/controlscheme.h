#pragma once
#ifndef ROCKET_CONTROLSCHEME_INCLUDED
#define ROCKET_CONTROLSCHEME_INCLUDED

#include "input.h"
#include <string>
#include <vector>

namespace Rocket
{
    namespace Implementation
    {
        struct ButtonKeyMap
        {
            std::string Name;
            Input::KeyCode Key;
        };

        struct AxisKeyMap
        {
            std::string Name;
            Input::KeyCode KeyDown;
            Input::KeyCode KeyUp;
        };

        class ControlScheme final : public Input::IControlScheme
        {
        public:
            ControlScheme(const char* name);
            ~ControlScheme();

            virtual const char* Name() const;
            virtual void AddButton(const char* name);
            virtual void AddAxis(const char* name);

            virtual void AddButtonKeyboardMapping(const char* name, Input::KeyCode keycode);
            virtual void AddAxisKeyboardMapping(const char* name, Input::KeyCode down, Input::KeyCode up);

            const char* GetButtonName(size_t index) const;
            size_t GetNumButtons() const;

            const char* GetAxisName(size_t index) const;
            size_t GetNumAxis() const;

            const ButtonKeyMap* GetButtonKeyMap(size_t index) const;
            size_t GetNumButtonKeyMaps() const;

            const AxisKeyMap* GetAxisKeyMap(size_t index) const;
            size_t GetNumAxisKeyMaps() const;

        private:
            ControlScheme(const ControlScheme&);
            const ControlScheme& operator=(const ControlScheme&);

            std::string m_name;

            std::vector<std::string> m_buttons;
            std::vector<std::string> m_axis;

            std::vector<ButtonKeyMap*> m_buttonKeyMaps;
            std::vector<AxisKeyMap*> m_axisKeyMaps;
        };
    }
}

#endif
