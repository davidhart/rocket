#include "windows/windowsgameview.h"
#include "windows/windowsopenglrenderer.h"
#include "implementation/runtimecontrols.h"
#include "implementation/controlscheme.h"
#include <cassert>

#if defined(_WIN32)

#define WINDOWCLASSNAME "GameViewWindowClass"

using namespace Rocket;
using namespace Rocket::Windows;
using namespace Rocket::Input;
using namespace Rocket::Implementation;

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
    }

    return -1;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	if (umsg == WM_NCCREATE)
	{
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)((LPCREATESTRUCT)lparam)->lpCreateParams);
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	else
	{
		WindowsGameView* view = (WindowsGameView*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
		return view->WndProc(hwnd, umsg, wparam, lparam);
	}
}



WindowsRuntimeControls::WindowsRuntimeControls(Implementation::RuntimeControls* controls, Implementation::ControlScheme* scheme) :
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

    /*
    for (size_t i = 0; i < scheme->GetNumAxisKeyMaps(); ++i)
    {
        const AxisKeyMap* map = scheme->GetAxisKeyMap(i);

        int nativeUp = KeyCodeToNative(map->Up);
        int nativedown = KeyCodeToNative(map->Down);

        Axis* axis = controls->geTAxisInternal(map->Name.c - str());


    }
    */
}

const Implementation::RuntimeControls* WindowsRuntimeControls::RuntimeControls() const
{
    return m_controls;
}

void WindowsRuntimeControls::ButtonDown(Button* button)
{
    button->OnButtonDown();
}

void WindowsRuntimeControls::ButtonUp(Button* button)
{
    button->OnButtonUp();
}

void WindowsRuntimeControls::KeyDown(int nativeCode)
{
    auto it = m_keyDown.find(nativeCode);

    if (it != m_keyDown.end())
        it->second();
}

void WindowsRuntimeControls::KeyUp(int nativeCode)
{
    auto it = m_keyUp.find(nativeCode);

    if (it != m_keyUp.end())
        it->second();
}

WindowsGameView::WindowsGameView() :
	m_hwnd(0),
	m_isClassRegistered(false),
	m_isWindowClosed(false),
	m_isResizable(false)
{
}

WindowsGameView::~WindowsGameView()
{
    for (auto it = m_controls.begin(); it != m_controls.end(); ++it)
    {
        delete *it;
    }

	if (m_hwnd != NULL)
	{
		CloseWindow(m_hwnd);
	}

	if (m_isClassRegistered)
	{
		UnregisterClassA(WINDOWCLASSNAME, NULL);
	}
}

bool WindowsGameView::Create()
{
	HINSTANCE hinstance = (HINSTANCE)GetModuleHandleA(NULL);

	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEXA);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WINDOWCLASSNAME;
	wcex.hIconSm = NULL;

	ATOM windowclass = RegisterClassExA(&wcex);

	m_isClassRegistered = windowclass != 0;

	if (m_isClassRegistered == false)
	{
		return false;
	}

	m_hwnd = CreateWindowExA(
		WS_EX_APPWINDOW,
		WINDOWCLASSNAME,
		"",
		WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		NULL,
		NULL,
		hinstance,
		this
	);

	// TODO: correct window to be actually the right size

	m_size = ivec2(800, 600);

	if (m_hwnd == NULL)
	{
		return false;
	}

	return true;
}

Renderer* WindowsGameView::CreateRenderer()
{
	WindowsOpenGLRenderer* renderer = new WindowsOpenGLRenderer(m_hwnd);

	if (renderer->Create() == false)
	{
		delete renderer;
		return nullptr;
	}

	renderer->GameViewResized(m_size);

	AddSizeObserver(renderer);

	return renderer;
}

void WindowsGameView::ReleaseRenderer(Renderer* renderer)
{
	RemoveSizeObserver((WindowsOpenGLRenderer*)renderer);

	delete renderer;
}

void WindowsGameView::SetTitle(const char* title)
{
	SetWindowTextA(m_hwnd, title);
}

void WindowsGameView::Update(float delta)
{
    BaseGameView::Update(delta);

	MSG msg;
	while (PeekMessageW(&msg, m_hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

bool WindowsGameView::IsClosed()
{
	return m_isWindowClosed;
}

void WindowsGameView::SetIsResizable(bool isResizable)
{
	LONG style = GetWindowLongA(m_hwnd, GWL_STYLE);

	if (isResizable)
	{
		style |= WS_SIZEBOX;
	}
	else
	{
		style &= ~WS_SIZEBOX;
	}

	SetWindowLongA(m_hwnd, GWL_STYLE, style);

	m_isResizable = isResizable;
}

bool WindowsGameView::GetIsResizable()
{
	return m_isResizable;
}

ivec2 WindowsGameView::GetSize() const
{
	return m_size;
}

void WindowsGameView::RuntimeControlsActivated(Implementation::RuntimeControls* controls, Implementation::ControlScheme* scheme)
{
    WindowsRuntimeControls* wincontrols = new WindowsRuntimeControls(controls, scheme);

    m_controls.push_back(wincontrols);
}

void WindowsGameView::RuntimeControlsDeactivated(Implementation::RuntimeControls* controls)
{
    for (auto it = m_controls.begin(); it != m_controls.end(); ++it)
    {
        if ((*it)->RuntimeControls() == controls)
        {
            delete *it;
            m_controls.erase(it);
            return;
        }
    }

    assert(false); // Deactivating controls that are not active
}

LRESULT WindowsGameView::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_CLOSE:
		m_isWindowClosed = true;
		break;

	case WM_SIZE:
		m_size = ivec2(LOWORD(lparam), HIWORD(lparam));
		NotifySizeObservers(m_size);
		break;

    case WM_KEYDOWN:
        {
            for (size_t i = 0; i < m_controls.size(); ++i)
            {
                m_controls[i]->KeyDown(wparam);
            }
        }
        break;

    case WM_KEYUP:
        {
            for (size_t i = 0; i < m_controls.size(); ++i)
            {
                m_controls[i]->KeyUp(wparam);
            }
        }
        break;
	}

	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

#endif
