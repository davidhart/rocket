#include "game.h"
#include "gameview.h"
#include "renderer.h"

#include <thread>
#include <cassert>
#include <chrono>
#include <memory>

using namespace Rocket;
using namespace std::chrono;

class InternalGameServices : public GameServices
{
public:
    InternalGameServices(Rocket::GameView* view, Rocket::Renderer* renderer);
    virtual Rocket::GameView* GameView();
    virtual Rocket::Renderer* Renderer();

private:
    Rocket::GameView* m_view;
    Rocket::Renderer* m_renderer;
};

InternalGameServices::InternalGameServices(Rocket::GameView* view, Rocket::Renderer* renderer) :
    m_view(view),
    m_renderer(renderer)
{
}

GameView* InternalGameServices::GameView()
{
    return m_view;
}

Renderer* InternalGameServices::Renderer()
{
    return m_renderer;
}

int Game::Bootstrap(Game* game)
{
    GameView* view = GameView::Create("bootstrap");
    view->SetIsResizable(true);

    if (view == nullptr)
        return -1;

    Renderer* renderer = view->CreateRenderer();

    if (renderer == nullptr)
    {
        GameView::Release(view);
        return -1;
    }

    InternalGameServices services(view, renderer);

    game->Startup(&services);
    
    steady_clock::time_point prevTime = steady_clock::now();

    while (view->IsClosed() == false)
    {
        std::this_thread::sleep_for(seconds(0));

        steady_clock::time_point currentTime = steady_clock::now();

        float delta = duration<float>(currentTime - prevTime).count();

        view->Update(delta);

        game->Update(delta);

        renderer->Present();

        prevTime = currentTime;
    }


    game->Shutdown(&services);
    
    view->ReleaseRenderer(renderer);
    GameView::Release(view);

    // TODO: provide api for exiting with error code
    return 0;
}
