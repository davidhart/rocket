#include "windowsopenglrenderer.h"

#include "opengl/rocket_opengl.h"
#include "wglext.h"

#include "opengl/glbuffer.h"
#include "opengl/glshader.h"
#include "opengl/gltexture.h"
#include "opengl/gldrawbinding.h"

#include <cassert>
#include <cstdio>

using namespace Rocket;
using namespace Rocket::Windows;
using namespace Rocket::OpenGL;

void APIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	char* severitystr;
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW:
		severitystr = "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		severitystr = "MED";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		severitystr = "HIGH";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		severitystr = "INFO";
		break;
	default:
		assert(false); severitystr = "???";
	}

	// TODO: hookup with logging system
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

#if _DEBUG
	{
		wglMakeCurrent(m_hdc, m_hglrc);

		PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC)wglGetProcAddress("glDebugMessageCallbackARB");
		if (glDebugMessageCallbackARB != nullptr)
		{
			glDebugMessageCallbackARB(&DebugMessageCallback, nullptr);
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		}
		
		wglMakeCurrent(NULL, NULL);
	}
#endif

	return true;
}

Buffer* WindowsOpenGLRenderer::CreateBuffer(size_t size, void* data)
{
	wglMakeCurrent(m_hdc, m_hglrc);

	GLBuffer* buffer = new GLBuffer();

	if (buffer->Create(size, data) == false)
	{
		delete buffer;
		return nullptr;
	}

	return buffer;
}

void WindowsOpenGLRenderer::ReleaseBuffer(Buffer* buffer)
{
	delete buffer;
}

Shader* WindowsOpenGLRenderer::CreateShader(const ShaderDef& def)
{
	wglMakeCurrent(m_hdc, m_hglrc);

	GLShader* shader = new GLShader();
	
	if (shader->Create(def) == false)
	{
		delete shader;
		return nullptr;
	}

	return shader;
}

void WindowsOpenGLRenderer::ReleaseShader(Shader* shader)
{
	delete shader;
}

Texture* WindowsOpenGLRenderer::CreateTexture(const TextureDef& def)
{
	wglMakeCurrent(m_hdc, m_hglrc);

	GLTexture* texture = new GLTexture();

	if (texture->Create(def) == false)
	{
		delete texture;
		return nullptr;
	}

	return texture;
}

DrawBinding* WindowsOpenGLRenderer::CreateDrawBinding(const DrawBindingDef& def)
{
	wglMakeCurrent(m_hdc, m_hglrc);

	GLDrawBinding* binding = new GLDrawBinding();

	if (binding->Create(def) == false)
	{
		delete binding;
		return nullptr;
	}

	return binding;
}

void WindowsOpenGLRenderer::ReleaseDrawBinding(DrawBinding* binding)
{
	delete binding;
}

void WindowsOpenGLRenderer::ReleaseTexture(Texture* texture)
{
	delete texture;
}

void WindowsOpenGLRenderer::RenderTemp(DrawBinding* binding, Shader* shader)
{
	m_tempDrawQueue.push(TempDraw
	{
		binding, shader
	});
}

void WindowsOpenGLRenderer::Present()
{
	if (!wglMakeCurrent(m_hdc, m_hglrc))
	{
		return;
	}

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	while (m_tempDrawQueue.empty() == false)
	{
		TempDraw draw = m_tempDrawQueue.front();

		GLuint vaohandle = ((GLDrawBinding*)draw.binding)->GetNativeHandle();
		glBindVertexArray(vaohandle);

		GLuint shaderhandle = ((GLShader*)draw.shader)->GetNativeHandle();
		glUseProgram(shaderhandle);

		GLsizei numElements = ((GLDrawBinding*)draw.binding)->GetNumElements();
		glDrawArrays(GL_TRIANGLES, 0, numElements);

		m_tempDrawQueue.pop();
	}

	SwapBuffers(m_hdc);
}