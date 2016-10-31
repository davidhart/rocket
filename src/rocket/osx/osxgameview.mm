#include "osx/osxgameview.h"

#if defined(__APPLE__)

#include "osx/osxopenglrenderer.h"
#include "input.h"
#import <Cocoa/Cocoa.h>

using namespace Rocket;
using namespace Rocket::OSX;


@interface RocketApplication : NSApplication
{
}
@end

@implementation RocketApplication

- (void)empty:(id)object
{
    
}

@end


@interface RocketApplicationDelegate : NSObject
{
}
@end

@implementation RocketApplicationDelegate

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
    id windows = [sender windows];

    // Force close windows
    for (int i = 0; i < [windows count]; ++i)
    {
        NSWindow* window = [windows objectAtIndex:i];
        [window close];
    }
    
    // Cancel termination and allow window closed event to be detected so app can
    // terminate using standard flow
    return NSTerminateCancel;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    [NSApp stop:nil];
    
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    NSEvent* event = [NSEvent otherEventWithType:NSApplicationDefined
                                        location:NSMakePoint(0, 0)
                                   modifierFlags:0
                                       timestamp:0
                                    windowNumber:0
                                         context:nil
                                         subtype:0
                                           data1:0
                                           data2:0];
    [NSApp postEvent:event atStart:YES];
    [pool drain];
}

@end

@interface RocketOSXWindow : NSWindow
{
}
@end

@implementation RocketOSXWindow

- (BOOL)canBecomeKeyWindow
{
    return YES;
}

@end



@interface RocketOSXView : NSView <NSWindowDelegate>
{
    OSXGameView* gameView;
}
-(id)initWithGameView:(OSXGameView*)view;
-(void)windowWillClose:(NSNotification*)notif;
-(void)keyDown:(NSEvent *)event;
-(void)keyUp:(NSEvent *)event;
@end

@implementation RocketOSXView

-(id)initWithGameView:(OSXGameView *)view
{
    [super init];
    if (self != nil)
    {
        self->gameView = view;
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(surfaceNeedsUpdate:)
                                                     name:NSViewGlobalFrameDidChangeNotification
                                                   object:self];
    }
    return self;
}

-(void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:NSViewGlobalFrameDidChangeNotification
                                                  object:self];
    
    [super dealloc];
}

-(void)windowWillClose:(NSNotification*)notif
{
    gameView->WindowWillClose();
}

-(void)surfaceNeedsUpdate:(NSNotification*)notification
{
    NSRect frame = [self.window contentRectForFrameRect:self.window.frame];
    frame.origin = CGPointMake(0, 0);
    [self setFrame: frame];
    
    NSRect backing = [self convertRectToBacking:[self bounds]];
    
    gameView->NotifySizeObservers(ivec2((int)backing.size.width, (int)backing.size.height));
}

-(void)keyDown:(NSEvent *)event
{
    short kc = [event keyCode];
    gameView->KeyDown(reinterpret_cast<IKey*>(kc));
    
    [super keyDown: event];
}

-(void)keyUp:(NSEvent *)event
{
    short kc = [event keyCode];
    gameView->KeyUp(reinterpret_cast<IKey*>(kc));
    
    [super keyUp: event];
}

-(BOOL)acceptsFirstResponder
{
    return YES;
}

@end


static bool StaticSetupAppKit()
{
    if (NSApp)
        return true;
    
    [RocketApplication sharedApplication];
    
    [NSThread detachNewThreadSelector:@selector(empty:) toTarget:NSApp withObject:nil];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    
    id appdelegate = [[RocketApplicationDelegate alloc] init];
    
    [NSApp setDelegate:appdelegate];
    [NSApp run];
    
    return true;
}



OSXGameView::OSXGameView() :
    m_window(nullptr),
    m_view(nullptr),
    m_open(false)
{
    
}

OSXGameView::~OSXGameView()
{
    [((id)m_window) dealloc];
    [((id)m_view) dealloc];
}

bool OSXGameView::Create()
{
    if (StaticSetupAppKit() == false)
    {
        return false;
    }
    
    NSRect windowRect;
    windowRect.origin = CGPointMake(0.0f, 0.0f);
    windowRect.size = CGSizeMake(800.0f, 600.0f);
    
    NSWindowStyleMask windowStyle = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;
    
    RocketOSXWindow* window = [[RocketOSXWindow alloc]
                 initWithContentRect:windowRect
                 styleMask:windowStyle
                 backing:NSBackingStoreBuffered
                 defer:NO];
    
    RocketOSXView* view = [[RocketOSXView alloc]
              initWithGameView:this];
    
    [view setAutoresizingMask:NSViewWidthSizable|NSViewHeightSizable];
    
    // Request high dpi resolution
    [view setWantsBestResolutionOpenGLSurface:YES];
    
    [window setDelegate: view];
    [window makeFirstResponder:view];
    [window setContentView:view];
    [window setRestorable:NO];
    
    [window center];
    
    [NSApp activateIgnoringOtherApps:YES];
    [window makeKeyAndOrderFront:nil];
    
    m_window = (void*)window;
    m_view = (void*)view;
    
    // Size must be re-calculated from NSView backing format
    NSRect backing = [view convertRectToBacking:[view bounds]];
    m_size = ivec2(backing.size.width, backing.size.height);
    
    if (m_window == nil || m_view == nil)
    {
        return false;
    }
    
    m_open = true;
    return true;
}

Renderer* OSXGameView::CreateRenderer()
{
    OSXOpenGLRenderer* renderer = new OSXOpenGLRenderer(m_view);
    
    if (renderer->Create() == false)
    {
        delete renderer;
        return nullptr;
    }
    
	renderer->GameViewResized(m_size);
    AddSizeObserver(renderer);
    
    return renderer;
}

void OSXGameView::ReleaseRenderer(Renderer* renderer)
{
    RemoveSizeObserver((OSXOpenGLRenderer*)renderer);
    
    delete renderer;
}

void OSXGameView::SetTitle(const char* title)
{
    [((id)m_window) setTitle:[NSString stringWithUTF8String:title]];
}

void OSXGameView::SetIsResizable(bool isResizable)
{
    NSWindow* window = (id)m_window;
    
    if (isResizable)
    {
        [window setStyleMask: [window styleMask] | NSResizableWindowMask];
    }
    else
    {
        [window setStyleMask: [window styleMask] & ~NSResizableWindowMask];
    }
}

bool OSXGameView::GetIsResizable()
{
    return ([((id)m_window) styleMask] & NSResizableWindowMask) == NSResizableWindowMask;
}

void OSXGameView::Update(float dt)
{
    BaseGameView::Update(dt);
    
    for (;;)
    {
        NSEvent* event = [NSApp nextEventMatchingMask:NSAnyEventMask
                                            untilDate:[NSDate distantPast]
                                               inMode:NSDefaultRunLoopMode
                                              dequeue:YES];
        if (event == nil)
            break;
        
        [NSApp sendEvent:event];
    }
}

bool OSXGameView::IsClosed()
{
    return m_open == false;
}

void OSXGameView::WindowWillClose()
{
    m_open = false;
}

void OSXGameView::NotifySizeObservers(const ivec2 &size)
{
    m_size = size;
    BaseGameView::NotifySizeObservers(size);
}

IKey* OSXGameView::GetKey(KeyCode code)
{
    return reinterpret_cast<IKey*>(49);
}

void OSXGameView::SetKeyboardMapping(const char* name, IKey* key)
{
    Input::PressAction* action = GetPressActionInternal(name);
    
    m_keyboardMapping[key] = action;
}

void OSXGameView::KeyDown(IKey* key)
{
    auto it = m_keyboardMapping.find(key);
    
    if (it != m_keyboardMapping.end())
    {
        it->second->Down();
    }
}

void OSXGameView::KeyUp(IKey* key)
{
    auto it = m_keyboardMapping.find(key);
    
    if (it != m_keyboardMapping.end())
    {
        it->second->Up();
    }
}

#endif
