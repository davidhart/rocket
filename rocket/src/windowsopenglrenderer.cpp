#include "windowsopenglrenderer.h"

#include "opengl/rocket_opengl.h"
#include "wglext.h"

using namespace Rocket::Windows;
using namespace Rocket::OpenGL;

WindowsOpenGLRenderer::WindowsOpenGLRenderer(HWND hwnd) :
	m_hwnd(hwnd)
{

}

WindowsOpenGLRenderer::~WindowsOpenGLRenderer()
{
	if (m_hglrc != NULL)
	{
		wglMakeCurrent(m_hdc, NULL);
	}

	wglDeleteContext(m_hglrc);
}

bool WindowsOpenGLRenderer::Create()
{
	// Create an OpenGL 3.0 context, with no fallback if 3.0 core is not supported
	m_hdc = GetDC(m_hwnd);

	if (m_hdc == NULL)
	{
		return false;
	}

	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Depth buffer
		8,											// 8-bit Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	int pf = ChoosePixelFormat(m_hdc, &pfd);

	if (pf == 0)
	{
		return false;
	}

	if (!SetPixelFormat(m_hdc, pf, &pfd))
	{
		return false;
	}

	HGLRC tempHglrc = wglCreateContext(m_hdc);

	if (tempHglrc == NULL)
	{
		return false;
	}

	wglMakeCurrent(m_hdc, tempHglrc);

	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	if (Platform::IsInitialized() == false)
	{
		Platform::Initialize((Platform::GetProcImpl)wglGetProcAddress);
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(tempHglrc);
	
	if (wglChoosePixelFormatARB == nullptr || wglCreateContextAttribsARB == nullptr)
	{
		return false;
	}

	int pfAttribs[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0 // Terminator
	};

	int pixelFormat;
	UINT numFormats;

	if (wglChoosePixelFormatARB(m_hdc, pfAttribs, NULL, 1, &pixelFormat, &numFormats) == false)
	{
		// No supported pixel formats
		return false;
	}

	int contextAttribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 0,
		WGL_CONTEXT_FLAGS_ARB, 0,
		0 // Terminator
	};

	m_hglrc = wglCreateContextAttribsARB(m_hdc, NULL, contextAttribs);

	if (m_hglrc == NULL)
	{
		return false;
	}
	
	return true;
}

void WindowsOpenGLRenderer::Present()
{
	if (!wglMakeCurrent(m_hdc, m_hglrc))
	{
		return;
	}

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	SwapBuffers(m_hdc);
}