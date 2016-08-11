#include "windowsgameviewimpl.h"

#define WINDOWCLASSNAME "GameViewWindowClass"

using namespace Rocket::Windows;

LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	if (umsg == WM_NCCREATE)
	{
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)((LPCREATESTRUCT)lparam)->lpCreateParams);
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	else
	{
		WindowsGameViewImpl* view = (WindowsGameViewImpl*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
		return view->WndProc(hwnd, umsg, wparam, lparam);
	}
}

WindowsGameViewImpl::WindowsGameViewImpl() :
	m_hwnd(0),
	m_isWindowClosed(false)
{
}

WindowsGameViewImpl::~WindowsGameViewImpl()
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

bool WindowsGameViewImpl::Create()
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

	if (m_hwnd == NULL)
	{
		return false;
	}

	return true;
}

void WindowsGameViewImpl::SetTitle(const char* title)
{
	SetWindowTextA(m_hwnd, title);
}

void WindowsGameViewImpl::FlushEvents()
{
	MSG msg;
	while (PeekMessageW(&msg, m_hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

bool WindowsGameViewImpl::IsClosed()
{
	return m_isWindowClosed;
}

LRESULT WindowsGameViewImpl::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	if (umsg == WM_CLOSE)
	{
		m_isWindowClosed = true;
	}

	return DefWindowProc(hwnd, umsg, wparam, lparam);
}