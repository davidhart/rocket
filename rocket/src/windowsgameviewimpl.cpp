#include "windowsgameviewimpl.h"

#define WINDOWCLASSNAME L"GameViewWindowClass"

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
	hwnd(0),
	isWindowClosed(false)
{
}

WindowsGameViewImpl::~WindowsGameViewImpl()
{
	if (hwnd != NULL)
	{
		CloseWindow(hwnd);
	}

	if (isClassRegistered)
	{
		UnregisterClassW(WINDOWCLASSNAME, NULL);
	}
}

bool WindowsGameViewImpl::Create()
{
	HINSTANCE hinstance = (HINSTANCE)GetModuleHandleW(NULL);

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEXW);
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

	ATOM windowclass = RegisterClassExW(&wcex);

	isClassRegistered = windowclass != 0;

	if (isClassRegistered == false)
	{
		return false;
	}

	hwnd = CreateWindowExW(
		WS_EX_APPWINDOW,
		WINDOWCLASSNAME,
		L"",
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

	if (hwnd == NULL)
	{
		return false;
	}

	return true;
}

void WindowsGameViewImpl::SetTitle(const wchar_t* title)
{
	SetWindowTextW(hwnd, title);
}

void WindowsGameViewImpl::FlushEvents()
{
	MSG msg;
	while (PeekMessageW(&msg, hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

bool WindowsGameViewImpl::IsClosed()
{
	return isWindowClosed;
}

LRESULT WindowsGameViewImpl::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	if (umsg == WM_CLOSE)
	{
		isWindowClosed = true;
	}

	return DefWindowProc(hwnd, umsg, wparam, lparam);
}