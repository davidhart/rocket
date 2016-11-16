#pragma once
#ifndef ROCKET_OSXOPENGLRENDERER_INCLUDED
#define ROCKET_OSXOPENGLRENDERER_INCLUDED

#if __APPLE__

#include "gameview.h"
#include "opengl/baseopenglrenderer.h"

namespace Rocket
{
    namespace OSX
    {
        class OSXOpenGLRenderer : public BaseOpenGLRenderer
        {
        public:
            OSXOpenGLRenderer(void* view);
            virtual ~OSXOpenGLRenderer();
            
            virtual bool CreateContext();
            virtual void SwapBuffers();
            
            virtual void GameViewResized(const ivec2& size);
            
        private:
            void* m_view;
            void* m_nsglcontext;
            void* m_pixelformat;
        };
    }
}

#endif

#endif
