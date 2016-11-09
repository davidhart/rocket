#include "implementation/runtimekeyboard.h"

#include "implementation/controlscheme.h"
#include "input.h"
#include <cassert>

using namespace Rocket;
using namespace Rocket::Input;
using namespace Rocket::Implementation;

RuntimeKeyboard::RuntimeKeyboard(
    RuntimeControls* controls,
    ControlScheme* scheme,
    IRuntimeKeyboardTranslator* translator) :
    m_controls(controls)
{
    for (size_t i = 0; i < scheme->GetNumButtonKeyMaps(); ++i)
    {
        const ButtonKeyMap* map = scheme->GetButtonKeyMap(i);

        int native = translator->TranslateKeyCodeToNative(map->Key);

        Button* button = controls->GetButtonInternal(map->Name.c_str());

        m_keyDown[native] = std::bind(ButtonDown, button);
        m_keyUp[native] = std::bind(ButtonUp, button);
    }

    // Must not be resized from here-in, pointers to members are held by std::functions
    m_keyboardAxis.resize(scheme->GetNumAxisKeyMaps());
    
    for (size_t i = 0; i < scheme->GetNumAxisKeyMaps(); ++i)
    {
        const AxisKeyMap* map = scheme->GetAxisKeyMap(i);

        int nativeUp = translator->TranslateKeyCodeToNative(map->KeyUp);
        int nativeDown = translator->TranslateKeyCodeToNative(map->KeyDown);

        Axis* axis = controls->GetAxisInternal(map->Name.c_str());
        KeyboardAxisProvider* axisProvider = m_keyboardAxis.data() + i;

        m_keyDown[nativeUp] = std::bind(AxisUp, axis, axisProvider, true);
        m_keyUp[nativeUp] = std::bind(AxisUp, axis, axisProvider, false);

        m_keyDown[nativeDown] = std::bind(AxisDown, axis, axisProvider, true);
        m_keyUp[nativeDown] = std::bind(AxisDown, axis, axisProvider, false);
    }
}

const RuntimeControls* RuntimeKeyboard::ActiveControls() const
{
    return m_controls;
}

void RuntimeKeyboard::ButtonDown(Button* button)
{
    button->OnButtonDown();
}

void RuntimeKeyboard::ButtonUp(Button* button)
{
    button->OnButtonUp();
}

void RuntimeKeyboard::AxisUp(Axis* axis, KeyboardAxisProvider* provider, bool pressed)
{
    axis->SetProvider(provider);
    provider->SetUpKeyState(pressed);
}

void RuntimeKeyboard::AxisDown(Axis* axis, KeyboardAxisProvider* provider, bool pressed)
{
    axis->SetProvider(provider);
    provider->SetDownKeyState(pressed);
}

void RuntimeKeyboard::KeyDown(int nativeCode)
{
    auto it = m_keyDown.find(nativeCode);

    if (it != m_keyDown.end())
        it->second();
}

void RuntimeKeyboard::KeyUp(int nativeCode)
{
    auto it = m_keyUp.find(nativeCode);

    if (it != m_keyUp.end())
        it->second();
}

