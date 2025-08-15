#include "RenderingManager.h"

RenderingManager* RenderingManager::m_RenderingManagerInstance = nullptr;

RenderingManager::RenderingManager()
{

}

RenderingManager* RenderingManager::GetInstance()
{
    if (m_RenderingManagerInstance == nullptr)
    {
        m_RenderingManagerInstance = new RenderingManager();
    }
    return m_RenderingManagerInstance;
}

bool RenderingManager::TryInit(std::size_t screenWidth, std::size_t screenHeight)
{
    m_window = SDL_CreateWindow(
        "DIY Space Invaders",
        screenWidth,
        screenHeight,
        NULL);

    if (m_window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << '\n';
        return false;
    }
    m_renderer = SDL_CreateRenderer(m_window, NULL);
    if (!m_renderer) {
        std::cout << "Error creating SDL renderer.\n";
    }
    return true;
}

SDL_Renderer* RenderingManager::GetRenderer()
{
    return m_renderer;
}

SDL_Texture* RenderingManager::LoadTexture(const char* texturePath)
{
    return IMG_LoadTexture(m_renderer, texturePath);
}

void RenderingManager::Update()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(m_renderer);  /* start with a blank canvas. */

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  /* white text, full alpha */
    for (const auto& [text, textInfo] : UIManager::GetInstance()->GetCurrentTextsList())
    {
        SDL_SetRenderScale(m_renderer, textInfo.scale, textInfo.scale);
        SDL_RenderDebugText(m_renderer, textInfo.x, textInfo.y, textInfo.text.c_str());
    }
    if (GameStateManager::GetInstance()->GetGameState() == GameStateManager::InGame)
    {
        SDL_SetRenderScale(m_renderer, 1.0f, 1.0f);
        for (const auto gameObject : GameObjectManager::GetInstance()->GetGameObjects())
        {
            SDL_RenderTexture(RenderingManager::GetInstance()->GetRenderer(), gameObject->GetTexture(), gameObject->GetSrcPos(), gameObject->GetDestPos());
        }
    }
    SDL_RenderPresent(m_renderer);
}

RenderingManager::~RenderingManager()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

