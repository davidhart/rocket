#include "implementation/basegameview.h"

using namespace Rocket;
using namespace Rocket::Implementation;

void BaseGameView::AddSizeObserver(IGameViewSizeObserver* observer)
{
	m_sizeObservers.push_back(observer);
}

void BaseGameView::RemoveSizeObserver(IGameViewSizeObserver* observer)
{
	for (auto it = m_sizeObservers.begin(); it != m_sizeObservers.end(); )
	{
		if (*it == observer)
			it = m_sizeObservers.erase(it);
		else
			++it;
	}
}

void BaseGameView::NotifySizeObservers(const ivec2& size)
{
	for (size_t i = 0; i < m_sizeObservers.size(); ++i)
	{
		m_sizeObservers[i]->GameViewResized(size);
	}
}