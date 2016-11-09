#include "osx/osxgameview.h"

#if defined(__APPLE__)

#include "osx/osxopenglrenderer.h"
#include "input.h"
#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>

using namespace Rocket;
using namespace Rocket::OSX;
using namespace Rocket::Implementation;
using namespace Rocket::Input;

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
    gameView->NativeKeyDown((int)[event keyCode]);
    
    [super keyDown: event];
}

-(void)keyUp:(NSEvent *)event
{
    gameView->NativeKeyUp((int)[event keyCode]);
    
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

int OSXGameView::TranslateKeyCodeToNative(Input::KeyCode keycode)
{
    // Apple virtual keycodes are all over the place so this seems to be
    // the correct way to map them. Untested on exotic keyboard layouts
    switch(keycode)
    {
        case KEY_A: return kVK_ANSI_A;
        case KEY_B: return kVK_ANSI_B;
        case KEY_C: return kVK_ANSI_C;
        case KEY_D: return kVK_ANSI_D;
        case KEY_E: return kVK_ANSI_E;
        case KEY_F: return kVK_ANSI_F;
        case KEY_G: return kVK_ANSI_G;
        case KEY_H: return kVK_ANSI_H;
        case KEY_I: return kVK_ANSI_I;
        case KEY_J: return kVK_ANSI_J;
        case KEY_K: return kVK_ANSI_K;
        case KEY_L: return kVK_ANSI_L;
        case KEY_M: return kVK_ANSI_M;
        case KEY_N: return kVK_ANSI_N;
        case KEY_O: return kVK_ANSI_O;
        case KEY_P: return kVK_ANSI_P;
        case KEY_Q: return kVK_ANSI_Q;
        case KEY_R: return kVK_ANSI_R;
        case KEY_S: return kVK_ANSI_S;
        case KEY_T: return kVK_ANSI_T;
        case KEY_U: return kVK_ANSI_U;
        case KEY_V: return kVK_ANSI_V;
        case KEY_W: return kVK_ANSI_W;
        case KEY_X: return kVK_ANSI_X;
        case KEY_Y: return kVK_ANSI_Y;
        case KEY_Z: return kVK_ANSI_Z;
        case KEY_0: return kVK_ANSI_0;
        case KEY_1: return kVK_ANSI_1;
        case KEY_2: return kVK_ANSI_2;
        case KEY_3: return kVK_ANSI_3;
        case KEY_4: return kVK_ANSI_4;
        case KEY_5: return kVK_ANSI_5;
        case KEY_6: return kVK_ANSI_6;
        case KEY_7: return kVK_ANSI_7;
        case KEY_8: return kVK_ANSI_8;
        case KEY_9: return kVK_ANSI_9;
            
        case KEY_SPACE: return kVK_Space;
        case KEY_LEFT: return kVK_LeftArrow;
        case KEY_RIGHT: return kVK_RightArrow;
        case KEY_UP: return kVK_UpArrow;
        case KEY_DOWN: return kVK_DownArrow;
            
        default: break;
    }
    
    assert(false); // Unsupported KeyCode
    
    return 0;
}

#endif
