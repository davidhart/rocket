#pragma once
#ifndef ROCKET_INPUT_INCLUDED
#define ROCKET_INPUT_INCLUDED

#include "api.h"

namespace Rocket
{
    namespace Input
    {        
        class IPressAction
        {
        public:
            virtual bool IsDown() = 0;
            virtual bool Pressed() = 0;
            virtual bool Released() = 0;
        };

        class PressAction : public IPressAction
        {
        public:
            PressAction();
            virtual bool IsDown();
            virtual bool Pressed();
            virtual bool Released();

            void Down();
            void Up();
            void Reset();
            void Update();

        private:
            bool m_down;
            bool m_pressed;
            bool m_released;
        };
    }
}

#endif