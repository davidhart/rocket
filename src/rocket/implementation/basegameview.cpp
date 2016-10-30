#include "implementation/basegameview.h"

#include "input.h"

#include <cassert>

using namespace Rocket;
using namespace Rocket::Implementation;
using namespace Rocket::Input;

BaseGameView::~BaseGameView()
{
    for(auto it = m_pressActions.begin(); it != m_pressActions.end(); ++it)
    {
        delete it->second;
    }
}

void BaseGameView::Update(float)
{
    for (auto it = m_pressActions.begin(); it != m_pressActions.end(); ++it)
    {
        it->second->Update();
    }
}

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

IPressAction* BaseGameView::AddPressAction(const char* name)
{
    std::string key(name);

    assert(m_pressActions.find(key) == m_pressActions.end()); // Press action with that name already exists

    PressAction* action = new PressAction();

    m_pressActions[key] = action;

    return action;
}

IPressAction* BaseGameView::GetPressAction(const char* name)
{
    std::string key(name);

    assert(m_pressActions.find(key) != m_pressActions.end()); // Press action does not exist

    return m_pressActions.at(key);
}

void BaseGameView::RemovePressAction(const char* name)
{
    std::string key(name);

    assert(m_pressActions.find(key) != m_pressActions.end()); // Removing action which does not exist

    m_pressActions.erase(key);
}

PressAction* BaseGameView::GetPressActionInternal(const char* name)
{
    std::string key(name);

    assert(m_pressActions.find(key) != m_pressActions.end()); // Press action does not exist

    return m_pressActions.at(key);
}