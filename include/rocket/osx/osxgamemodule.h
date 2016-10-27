#pragma once
#ifndef ROCKET_OSXGAMEMODULE_INCLUDED
#define ROCKET_OSXGAMEMODULE_INCLUDED

#include "gamemodule.h"

#if defined(__APPLE__)

namespace Rocket
{
    namespace OSX
    {
        class OSXGameModule : public GameModule
        {
        public:
            OSXGameModule();
            virtual ~OSXGameModule();
            
            bool Create(const char* name);
            
            virtual Game* CreateGame(Renderer* renderer);
            virtual void ReleaseGame(Game* game);
        private:
            void* m_handle;
            GameModuleCreateProc m_createproc;
            GameModuleReleaseProc m_releaseproc;
        };
    }
}

#endif

#endif
