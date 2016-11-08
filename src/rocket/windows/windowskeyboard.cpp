#include "windows/windowskeyboard.h"

#if defined(_WIN32)

#include "implementation/controlscheme.h"
#include "input.h"
#include <Windows.h>
#include <cassert>

using namespace Rocket;
using namespace Rocket::Input;
using namespace Rocket::Implementation;
using namespace Rocket::Windows;

int KeyCodeToNative(KeyCode code)
{
    if (code >= KEY_A && code <= KEY_Z)
        return 0x41 + (code - KEY_A);

    if (code >= KEY_0 && code <= KEY_9)
        return 0x30 + (code - KEY_0);

    switch (code)
    {
    case KEY_SPACE:
        return VK_SPACE;
    case KEY_LEFT:
        return VK_LEFT;
    case KEY_RIGHT:
        return VK_RIGHT;
    case KEY_DOWN:
        return VK_DOWN;
    case KEY_UP:
        return VK_UP;
    }

    assert(false); // Unsupported keycode
    return -1;
}

WindowsKeyboard::WindowsKeyboard(Implementation::RuntimeControls* controls, Implementation::ControlScheme* scheme) :
    m_controls(controls)
{
    for (size_t i = 0; i < scheme->GetNumButtonKeyMaps(); ++i)
    {
        const ButtonKeyMap* map = scheme->GetButtonKeyMap(i);

        int native = KeyCodeToNative(map->Key);

        Button* button = controls->GetButtonInternal(map->Name.c_str());

        m_keyDown[native] = std::bind(ButtonDown, button);
        m_keyUp[native] = std::bind(ButtonUp, button);
    }

    // Must not be resized from here-in, pointers to members are held by std::functions
    m_keyboardAxis.resize(scheme->GetNumAxisKeyMaps());
    
    for (size_t i = 0; i < scheme->GetNumAxisKeyMaps(); ++i)
    {
        const AxisKeyMap* map = scheme->GetAxisKeyMap(i);

        int nativeUp = KeyCodeToNative(map->KeyUp);
        int nativeDown = KeyCodeToNative(map->KeyDown);

        Axis* axis = controls->GetAxisInternal(map->Name.c_str());
        KeyboardAxisProvider* axisProvider = m_keyboardAxis.data() + i;

        m_keyDown[nativeUp] = std::bind(AxisUp, axis, axisProvider, true);
        m_keyUp[nativeUp] = std::bind(AxisUp, axis, axisProvider, false);

        m_keyDown[nativeDown] = std::bind(AxisDown, axis, axisProvider, true);
        m_keyUp[nativeDown] = std::bind(AxisDown, axis, axisProvider, false);
    }
}

const Implementation::RuntimeControls* WindowsKeyboard::ActiveControls() const
{
    return m_controls;
}

void WindowsKeyboard::ButtonDown(Button* button)
{
    button->OnButtonDown();
}

void WindowsKeyboard::ButtonUp(Button* button)
{
    button->OnButtonUp();
}

void WindowsKeyboard::AxisUp(Axis* axis, KeyboardAxisProvider* provider, bool pressed)
{
    axis->SetProvider(provider);
    provider->SetUpKeyState(pressed);
}

void WindowsKeyboard::AxisDown(Axis* axis, KeyboardAxisProvider* provider, bool pressed)
{
    axis->SetProvider(provider);
    provider->SetDownKeyState(pressed);
}

void WindowsKeyboard::KeyDown(int nativeCode)
{
    auto it = m_keyDown.find(nativeCode);

    if (it != m_keyDown.end())
        it->second();
}

void WindowsKeyboard::KeyUp(int nativeCode)
{
    auto it = m_keyUp.find(nativeCode);

    if (it != m_keyUp.end())
        it->second();
}

#endif