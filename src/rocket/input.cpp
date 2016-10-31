#include "input.h"

using namespace Rocket::Input;

IPressAction::~IPressAction()
{
}

PressAction::PressAction() :
    m_down(false),
    m_pressed(false),
    m_released(false)
{
    
}

void PressAction::Down()
{
    // Cancel out auto-repeat
    if (m_down == false) m_pressed = true;

    m_down = true;
}

void PressAction::Up()
{
    m_released = true;
    m_down = false;
}

void PressAction::Update()
{
    m_pressed = false;
    m_released = false;
}

bool PressAction::IsDown()
{
    return m_down;
}

bool PressAction::Pressed()
{
    return m_pressed;
}

bool PressAction::Released()
{
    return m_released;
}
