#include "implementation/controlscheme.h"

using namespace Rocket;
using namespace Rocket::Input;
using namespace Rocket::Implementation;

ControlScheme::ControlScheme(const char* name) :
    m_name(name)
{
}

ControlScheme::~ControlScheme()
{
    for (auto it = m_buttonKeyMaps.begin(); it != m_buttonKeyMaps.end(); ++it)
    {
        delete *it;
    }

    for (auto it = m_axisKeyMaps.begin(); it != m_axisKeyMaps.end(); ++it)
    {
        delete *it;
    }
}

const char* ControlScheme::Name() const
{
    return m_name.c_str();
}

void ControlScheme::AddButton(const char* name)
{
    m_buttons.push_back(name);
}

void ControlScheme::AddAxis(const char* name)
{
    m_axis.push_back(name);
}

void ControlScheme::AddButtonKeyboardMapping(const char* name, Input::KeyCode key)
{
    ButtonKeyMap* map = new ButtonKeyMap();
    map->Name = name;
    map->Key = key;

    m_buttonKeyMaps.push_back(map);
}

void ControlScheme::AddAxisKeyboardMapping(const char* name, Input::KeyCode down, Input::KeyCode up)
{
    AxisKeyMap* mapping = new AxisKeyMap();
    mapping->Name = name;
    mapping->KeyDown = down;
    mapping->KeyUp = up;

    m_axisKeyMaps.push_back(mapping);
}

const char* ControlScheme::GetButtonName(size_t index) const
{
    return m_buttons[index].c_str();
}

size_t ControlScheme::GetNumButtons() const
{
    return m_buttons.size();
}

const char* ControlScheme::GetAxisName(size_t index) const
{
    return m_axis[index].c_str();
}

size_t ControlScheme::GetNumAxis() const
{
    return m_axis.size();
}

const ButtonKeyMap* ControlScheme::GetButtonKeyMap(size_t index) const
{
    return m_buttonKeyMaps[index];
}

size_t ControlScheme::GetNumButtonKeyMaps() const
{
    return m_buttonKeyMaps.size();
}

const AxisKeyMap* ControlScheme::GetAxisKeyMap(size_t index) const
{
    return m_axisKeyMaps[index];
}

size_t ControlScheme::GetNumAxisKeyMaps() const
{
    return m_axisKeyMaps.size();
}