#pragma once
#ifndef ROCKET_OSXGAMEVIEW_INCLUDED
#define ROCKET_OSXGAMEVIEW_INCLUDED

#include "implementation/basegameview.h"

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
    
            virtual void FlushEvents();
            virtual bool IsClosed();
            
            void WindowWillClose();
            
            virtual void NotifySizeObservers(const ivec2& size);
            
        private:
            void* m_window;
            void* m_view;
            bool m_open;
            ivec2 m_size;
        };
    }
}
#endif
