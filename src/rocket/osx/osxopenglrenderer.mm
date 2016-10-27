#include "osx/osxopenglrenderer.h"
#include "opengl/rocket_opengl.h"

#if defined(__APPLE__)

#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>

using namespace Rocket;
using namespace Rocket::OpenGL;
using namespace Rocket::OSX;

CFBundleRef OpenGLFramework;

void* getProcAddress(const char* name)
{
    CFStringRef symbolName = CFStringCreateWithCString(kCFAllocatorDefault,
                                                       name,
                                                       kCFStringEncodingASCII);
    
    void* symbol = CFBundleGetFunctionPointerForName(OpenGLFramework,
                                                     symbolName);
    
    CFRelease(symbolName);
    
    return symbol;
}

OSXOpenGLRenderer::OSXOpenGLRenderer(void* view) :
    m_view(view),
    m_nsglcontext(nullptr),
    m_pixelformat(nullptr)
{
    
}

OSXOpenGLRenderer::~OSXOpenGLRenderer()
{
    if (m_nsglcontext != nullptr)
        [((id)m_nsglcontext) dealloc];
    
    if (m_pixelformat != nullptr)
        [((id)m_pixelformat) dealloc];
}

bool OSXOpenGLRenderer::CreateContext()
{
    OpenGLFramework = CFBundleGetBundleWithIdentifier(CFSTR("com.apple.opengl"));
    assert(OpenGLFramework);
    
    NSOpenGLPixelFormatAttribute attributes[] =
    {
        NSOpenGLPFAAccelerated,
        NSOpenGLPFAClosestPolicy,
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAStencilSize, 8,
        NSOpenGLPFADoubleBuffer,
        0
    };
    
    NSOpenGLPixelFormat* pixelformat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
    
    NSOpenGLContext* nsglcontext = [[NSOpenGLContext alloc] initWithFormat:pixelformat shareContext:nil];
    
    [nsglcontext setView: ((id)m_view)];
    
    m_pixelformat = (void*)pixelformat;
    m_nsglcontext = (void*)nsglcontext;
    
    ActivateContext();
    
    if (Platform::IsInitialized() == false)
    {
        Platform::Initialize((Platform::GetProcImpl)getProcAddress);
    }
    
    DeactivateContext();
    
    return true;
}

void OSXOpenGLRenderer::ActivateContext()
{
    [((id)m_nsglcontext) makeCurrentContext];
}

void OSXOpenGLRenderer::DeactivateContext()
{
    [NSOpenGLContext clearCurrentContext];
}

void OSXOpenGLRenderer::SwapBuffers()
{
    [((id)m_nsglcontext) flushBuffer];
}

void OSXOpenGLRenderer::GameViewResized(const ivec2& size)
{
    [(NSOpenGLContext*)m_nsglcontext update];
    
    BaseOpenGLRenderer::GameViewResized(size);
}

#endif
