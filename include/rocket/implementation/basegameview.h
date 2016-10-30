#pragma once
#ifndef ROCKET_BASEGAMEVIEW_INCLUDED
#define ROCKET_BASEGAMEVIEW_INCLUDED

#include "gameview.h"
#include <vector>
#include <map>
#include <string>

namespace Rocket
{
    namespace Input
    {
        class PressAction;
    }

	namespace Implementation
	{
		class BaseGameView : public GameView
		{
		public:
            virtual ~BaseGameView();
            virtual void Update(float delta);

			virtual void AddSizeObserver(IGameViewSizeObserver* observer);
			virtual void RemoveSizeObserver(IGameViewSizeObserver* observer);
			virtual void NotifySizeObservers(const ivec2& size);

            virtual Input::IPressAction* AddPressAction(const char* name);
            virtual Input::IPressAction* GetPressAction(const char* name);
            virtual void RemovePressAction(const char* name);
            

        protected:
            virtual Input::PressAction* GetPressActionInternal(const char* name);

		private:
			std::vector<IGameViewSizeObserver*> m_sizeObservers;
            std::map<std::string, Input::PressAction*> m_pressActions;
		};
	}
}

#endif
