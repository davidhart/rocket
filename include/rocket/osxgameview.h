#pragma once
#ifndef ROCKET_OSXGAMEVIEW_INCLUDED
#define ROCKET_OSXGAMEVIEW_INCLUDED

#include "gameview.h"

namespace Rocket
{
    namespace OSX
    {
        class OSXGameView : public GameView
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
            
        private:
            void* m_window;
            void* m_view;
            bool m_open;
        };
    }
}
#endif
