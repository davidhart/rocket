#include "windows/windowsopenglrenderer.h"

#if defined(_WIN32)

#include "opengl/rocket_opengl.h"
#include "windows/wglext.h"

#include <cassert>
#include <cstdio>

using namespace Rocket;
using namespace Rocket::Windows;
using namespace Rocket::OpenGL;

void* getProcAddress(const char* name)
{
	return (void*)wglGetProcAddress(name);
}

void APIENTRY DebugMessageCallback(GLenum, GLenum, GLuint, GLenum severity, GLsizei, const GLchar *message, const void *)
{
	char* severitystr;
	bool log = false;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW:
		severitystr = "LOW";
		log = true;
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		severitystr = "MED";
		log = true;
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		severitystr = "HIGH";
		log = true;
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		severitystr = "INFO";
		break;
	default:
		assert(false); severitystr = "???";
	}

	// TODO: hookup with logging system
	if (log)
		std::fprintf(stderr, "[OpenGL][%s]%s\n", severitystr, message);
}

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

bool WindowsOpenGLRenderer::CreateContext()
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
		Platform::Initialize(getProcAddress);
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

	int contextFlags = 0;

#if _DEBUG
	contextFlags |= GL_CONTEXT_FLAG_DEBUG_BIT;
#endif

	int contextAttribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 0,
		WGL_CONTEXT_FLAGS_ARB, contextFlags,
		0 // Terminator
	};

	m_hglrc = wglCreateContextAttribsARB(m_hdc, NULL, contextAttribs);

	if (m_hglrc == NULL)
	{
		return false;
	}

	wglMakeCurrent(m_hdc, m_hglrc);
#if _DEBUG
	{

		PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC)wglGetProcAddress("glDebugMessageCallbackARB");
		if (glDebugMessageCallbackARB != nullptr)
		{
			glDebugMessageCallbackARB(&DebugMessageCallback, nullptr);
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		}
	}
#endif

	return true;
}

void WindowsOpenGLRenderer::SwapBuffers()
{
    ::SwapBuffers(m_hdc);
}

#endif
