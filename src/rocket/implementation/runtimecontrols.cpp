#include "implementation/runtimecontrols.h"
#include "implementation/controlscheme.h"
#include <cassert>

using namespace Rocket;
using namespace Rocket::Input;
using namespace Rocket::Implementation;

Button::Button() :
    m_isPressed(false),
    m_wasPressed(false),
    m_wasReleased(false)
{
}

bool Button::IsPressed()
{
    return m_isPressed;;
}

bool Button::WasJustPressed()
{
    return m_wasPressed;
}

bool Button::WasJustReleased()
{
    return m_wasReleased;
}

void Button::Update()
{
    m_wasPressed = false;
    m_wasReleased = false;
}

void Button::OnButtonDown()
{
    if (m_isPressed == false)
        m_wasPressed = true;
       
    m_isPressed = true;
}

void Button::OnButtonUp()
{
    if (m_isPressed == true)
        m_wasReleased = true;
    
    m_isPressed = false;
}

Axis::Axis() : 
    m_value(0)
{

}

float Axis::Value()
{
    return m_value;
}

void Axis::SetValue(float value)
{
    m_value = value;
}

RuntimeControls::RuntimeControls(ControlScheme* scheme)
{
    for (size_t i = 0; i < scheme->GetNumButtons(); ++i)
    {
        const char* name = scheme->GetButtonName(i);
        m_buttons[name] = new Button();
    }

    for (size_t i = 0; i < scheme->GetNumAxis(); ++i)
    {
        const char* name = scheme->GetAxisName(i);
        m_axis[name] = new Axis();
    }
}

RuntimeControls::~RuntimeControls()
{
    for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it)
        delete it->second;

    for (auto it = m_axis.begin(); it != m_axis.end(); ++it)
        delete it->second;
}

IButton* RuntimeControls::GetButton(const char* name)
{
    return GetButtonInternal(name);
}

IAxis* RuntimeControls::GetAxis(const char* name)
{
    return GetAxisInternal(name);
}

void RuntimeControls::Update(float)
{
    for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it)
    {
        it->second->Update();
    }
}

Button* RuntimeControls::GetButtonInternal(const char* name)
{
    std::string key(name);
    auto it = m_buttons.find(key);
    assert(it != m_buttons.end()); // Button not found
    return it->second;
}

Axis* RuntimeControls::GetAxisInternal(const char* name)
{
    std::string key(name);
    auto it = m_axis.find(key);
    assert(it != m_axis.end()); // Axis not found
    return it->second;
}