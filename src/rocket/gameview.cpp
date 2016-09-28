#include "gameview.h"
#include "windowsgameview.h"

using namespace Rocket;

GameView* GameView::Create(const char* title)
{
    GameView* view = nullptr;
    
#if _WINDOWS
    if (view != nullptr)
    {
        Windows::WindowsGameView* windowsview = new Windows::WindowsGameView();

        if (windowsview->Create() == false)
        {
            delete windowsview;
            return nullptr;
        }

        windowsview->SetTitle(title);
        view = windowsview;
    }
#endif
    
    
    
	return view;
}

void GameView::Release(GameView* view)
{
	delete view;
}

GameView::~GameView()
{

}
