#include "osxgameview.h"

#if __APPLE__

#include "osxopenglrenderer.h"
#import <Cocoa/Cocoa.h>

using namespace Rocket;
using namespace Rocket::OSX;


@interface RocketApplication : NSApplication
{
}
@end

@implementation RocketApplication

- (void)doNothing:(id)object
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
    // Force close windows
    
    // Cancel termination and allow window close to be detected
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



@interface RocketOSXView : NSView
{
    OSXGameView* gameView;
}
-(id)initWithGameView:(OSXGameView*)view;
@end

@implementation RocketOSXView

-(id)initWithGameView:(OSXGameView *)view
{
    [super init];
    if (self != nil)
    {
        self->gameView = view;
    }
    return self;
}

// TODO: respond to input events here

@end


static bool StaticSetupAppKit()
{
    if (NSApp)
        return true;
    
    [RocketApplication sharedApplication];
    
    [NSThread detachNewThreadSelector:@selector(doNothing:)
                             toTarget:NSApp
                           withObject:nil];
    
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    
    id appdelegate = [[RocketApplicationDelegate alloc] init];
    
    [NSApp setDelegate:appdelegate];
    [NSApp run];
    
    return true;
}



OSXGameView::OSXGameView() :
    m_window(nullptr),
    m_view(nullptr)
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
    
    NSWindowStyleMask windowStyle =
        NSResizableWindowMask | NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;
    
    id window = [[RocketOSXWindow alloc]
                 initWithContentRect:windowRect
                 styleMask:windowStyle
                 backing:NSBackingStoreBuffered
                 defer:NO];
    
    id view = [[RocketOSXView alloc]
              initWithGameView:this];
    
//    [view setWantsBestResolutionOpenGLSurface:YES];
    
    
    [window makeFirstResponder:view];
    [window setContentView:view];
    [window setRestorable:NO];
    
    [window center];
    
    [NSApp activateIgnoringOtherApps:YES];
    [window makeKeyAndOrderFront:nil];
    
    m_window = (void*)window;
    m_view = (void*)view;
    
    return m_window != nil && m_view != nil;
}

Renderer* OSXGameView::CreateRenderer()
{
    OSXOpenGLRenderer* renderer = new OSXOpenGLRenderer(m_view);
    
    if (renderer->Create() == false)
    {
        delete renderer;
        return nullptr;
    }
    
    return renderer;
}

void OSXGameView::ReleaseRenderer(Renderer* renderer)
{
    delete renderer;
}

void OSXGameView::SetTitle(const char* title)
{
    [((id)m_window) setTitle:[NSString stringWithUTF8String:title]];
}

void OSXGameView::SetIsResizable(bool isResizable)
{
    
}

bool OSXGameView::GetIsResizable()
{
    return true;
}

void OSXGameView::FlushEvents()
{
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
    return false;
}

#endif
