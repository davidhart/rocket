#include "implementation/basegameview.h"
#include "implementation/controlscheme.h"
#include "implementation/runtimecontrols.h"

#include <cassert>
#include <algorithm>

using namespace Rocket;
using namespace Rocket::Implementation;
using namespace Rocket::Input;

BaseGameView::~BaseGameView()
{
    for (auto it = m_runtimeControls.begin(); it != m_runtimeControls.end(); ++it)
    {
        delete it->second;
    }

    for (auto it = m_controlSchemes.begin(); it != m_controlSchemes.end(); ++it)
    {
        delete it->second;
    }
}

void BaseGameView::Update(float dt)
{
    for (auto it = m_runtimeControls.begin(); it != m_runtimeControls.end(); ++it)
    {
        it->second->Update(dt);
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

IControlScheme* BaseGameView::AddControlScheme(const char* name)
{
    std::string key(name);
    assert(m_controlSchemes.find(key) == m_controlSchemes.end()); // Control scheme already defined
    
    return m_controlSchemes[key] = new ControlScheme(name);
}

IControlScheme* BaseGameView::GetControlScheme(const char* name)
{
    auto it = m_controlSchemes.find(name);
    assert(it != m_controlSchemes.end()); // Control scheme not found
    return it->second;
}

void BaseGameView::RemoveControlScheme(const char* name)
{
    auto it = m_controlSchemes.find(name);
    assert(it != m_controlSchemes.end()); // Control scheme not found
    delete it->second;
    m_controlSchemes.erase(it);
}

IRuntimeControls* BaseGameView::ActivateControlScheme(const char* name)
{
    std::string key(name);
    auto schemeIt = m_controlSchemes.find(name);
    assert(schemeIt != m_controlSchemes.end()); // Control scheme not found
    assert(m_runtimeControls.find(key) == m_runtimeControls.end()); // Control scheme already active
    
    ControlScheme* scheme = schemeIt->second;
    RuntimeControls* controls = new RuntimeControls(scheme);
    
    m_keyboards.push_back(new RuntimeKeyboard(controls, scheme, this));
    
    m_runtimeControls[key] = controls;
    return controls;
}

IRuntimeControls* BaseGameView::GetActiveControlScheme(const char* name)
{
    auto it = m_runtimeControls.find(name);
    assert(it != m_runtimeControls.end()); // Control scheme not active
    return it->second;
}

void BaseGameView::DeactivateControlScheme(const char* name)
{
    auto controls_it = m_runtimeControls.find(name);
    assert(controls_it != m_runtimeControls.end()); // Control scheme not active

    RuntimeControls* controls = controls_it->second;
    m_runtimeControls.erase(controls_it);

    auto kb_it = std::find_if(m_keyboards.begin(), m_keyboards.end(), [controls] (RuntimeKeyboard* k) { return k->ActiveControls() == controls; });
    assert(kb_it != m_keyboards.end());
    
    delete *kb_it;
    m_keyboards.erase(kb_it);
    
    delete controls;
}

void BaseGameView::NativeKeyDown(int key)
{
    for (size_t i = 0; i < m_keyboards.size(); ++i)
        m_keyboards[i]->KeyDown(key);
}

void BaseGameView::NativeKeyUp(int key)
{
    for (size_t i = 0; i < m_keyboards.size(); ++i)
        m_keyboards[i]->KeyUp(key);
}
