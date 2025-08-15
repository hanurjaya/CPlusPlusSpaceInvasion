#pragma once
#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include "GameStateManager.h"
#include "GameObjectManager.h"
#include "UIManager.h"
class RenderingManager
{
private:
	SDL_Window* m_window{};
	SDL_Renderer* m_renderer{};
	static RenderingManager* m_RenderingManagerInstance;
	RenderingManager();
public:
	RenderingManager(RenderingManager&) = delete;
	void operator=(const RenderingManager&) = delete;
	static RenderingManager* GetInstance();
	bool TryInit(std::size_t screenWidth, std::size_t screenHeight);
	SDL_Renderer* GetRenderer();
	SDL_Texture* LoadTexture(const char* texturePath);
	void Update();
	~RenderingManager();
};

