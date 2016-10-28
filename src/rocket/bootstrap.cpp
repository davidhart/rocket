#include "bootstrap.h"
#include "gameview.h"
#include "renderer.h"
#include "game.h"

#include <thread>
#include <cassert>
#include <chrono>

using namespace Rocket;
using namespace std::chrono;

Bootstrap::Bootstrap() :
    m_view(nullptr),
    m_renderer(nullptr)
{

}

Bootstrap::~Bootstrap()
{
    if (m_renderer)
        m_view->ReleaseRenderer(m_renderer);

    if (m_view)
        GameView::Release(m_view);
}

bool Bootstrap::Start(const char* name)
{
    m_view = GameView::Create(name);

    if (m_view == nullptr)
        return false;

    m_renderer = m_view->CreateRenderer();

    if (m_renderer == nullptr)
        return false;

    return true;
}

void Bootstrap::Run(Game* game)
{
    steady_clock::time_point prevTime = steady_clock::now();

    while (m_view->IsClosed() == false)
    {
        std::this_thread::sleep_for(seconds(0));

        steady_clock::time_point currentTime = steady_clock::now();

        m_view->FlushEvents();

        duration<float> delta = duration<float>(currentTime - prevTime);

        game->Update(delta.count());

        m_renderer->Present();

        prevTime = currentTime;
    }
}

Renderer* Bootstrap::GetRenderer()
{
    return m_renderer;
}

GameView* Bootstrap::GetGameView()
{
    return m_view;
}
