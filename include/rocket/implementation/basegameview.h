#pragma once
#ifndef ROCKET_BASEGAMEVIEW_INCLUDED
#define ROCKET_BASEGAMEVIEW_INCLUDED

#include "gameview.h"
#include <vector>

namespace Rocket
{
	namespace Implementation
	{
		class BaseGameView : public GameView
		{
		public:
			virtual void AddSizeObserver(IGameViewSizeObserver* observer);
			virtual void RemoveSizeObserver(IGameViewSizeObserver* observer);
			virtual void NotifySizeObservers(const ivec2& size);

		private:
			std::vector<IGameViewSizeObserver*> m_sizeObservers;
		};
	}
}

#endif
