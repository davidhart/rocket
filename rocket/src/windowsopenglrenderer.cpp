#include "windowsopenglrenderer.h"

#include <gl/GL.h>

using namespace Rocket::Windows;

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
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
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

	m_hglrc = wglCreateContext(m_hdc);

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