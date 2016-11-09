#pragma once
#ifndef ROCKET_OSXGAMEVIEW_INCLUDED
#define ROCKET_OSXGAMEVIEW_INCLUDED

#include "implementation/basegameview.h"
#include <map>

#if defined (__APPLE__)

namespace Rocket
{
    namespace OSX
    {
        class OSXGameView : public Implementation::BaseGameView
        {
        public:
            OSXGameView();
            virtual ~OSXGameView();
            bool Create();
            
            virtual Renderer* CreateRenderer();
            virtual void ReleaseRenderer(Renderer* renderer);
    
            virtual void SetTitle(const char* title);
    
            virtual void SetIsResizable(bool isResizable);
            virtual bool GetIsResizable();
    
            virtual void Update(float dt);
            virtual bool IsClosed();
            
            void WindowWillClose();
            
            virtual void NotifySizeObservers(const ivec2& size);
            
            virtual int TranslateKeyCodeToNative(Input::KeyCode code);
            
        private:
            void* m_window;
            void* m_view;
            bool m_open;
            ivec2 m_size;
        };
    }
}

#endif

#endif
