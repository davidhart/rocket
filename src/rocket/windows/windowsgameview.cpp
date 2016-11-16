#include "windows/windowsgameview.h"
#include "windows/windowsopenglrenderer.h"
#include "implementation/runtimecontrols.h"
#include "implementation/controlscheme.h"
#include "implementation/runtimekeyboard.h"
#include <cassert>

#if defined(_WIN32)

#define WINDOWCLASSNAME "GameViewWindowClass"

using namespace Rocket;
using namespace Rocket::Windows;
using namespace Rocket::Input;
using namespace Rocket::Implementation;

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

WindowsGameView::WindowsGameView() :
	m_hwnd(0),
	m_isClassRegistered(false),
	m_isWindowClosed(false),
	m_isResizable(false)
{
}

WindowsGameView::~WindowsGameView()
{
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

int WindowsGameView::TranslateKeyCodeToNative(KeyCode code)
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
            NativeKeyDown((int)wparam);
        }
        break;

    case WM_KEYUP:
        {
            NativeKeyUp((int)wparam);
        }
        break;
	}

	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

#endif
