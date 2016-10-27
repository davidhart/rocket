#include "gameview.h"

#if defined(_WIN32)
#include "windows/windowsgameview.h"
#endif

#if defined(__APPLE__)
#include "osx/osxgameview.h"
#endif

using namespace Rocket;

GameView* GameView::Create(const char* title)
{
    GameView* view = nullptr;
    
#if _WIN32
    if (view == nullptr)
    {
        Windows::WindowsGameView* windowsview = new Windows::WindowsGameView();

        if (windowsview->Create())
        {
            view = windowsview;
        }
        else
        {
            delete windowsview;
        }
    }
#endif
    
#if __APPLE__
    if (view == nullptr)
    {
        OSX::OSXGameView* osxview = new OSX::OSXGameView();
        
        if (osxview->Create())
        {
            view = osxview;
        }
        else
        {
            delete osxview;
        }
    }
#endif
    
    if (view == nullptr)
        return nullptr;
    
    view->SetTitle(title);
    
	return view;
}

void GameView::Release(GameView* view)
{
	delete view;
}

GameView::~GameView()
{

}
