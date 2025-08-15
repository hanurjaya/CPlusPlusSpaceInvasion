#pragma once
#include <map>
#include <string>
#include <vector>
#include <SDL3/SDL_render.h>
#include "GameStateManager.h"
class UIManager
{
public:
	struct TextInfo
	{
		std::string text;
		float x;
		float y;
		float scale;
	};
private:
	std::map<GameStateManager::GameState, std::map<std::string, TextInfo>> m_stringList{};
	std::map<std::string, TextInfo> m_currentList{};
	static UIManager* m_UIManagerInstance;
	GameStateManager::GameState m_lastState = GameStateManager::Exit;
	UIManager();
public:
	UIManager(UIManager&) = delete;
	void operator=(const UIManager&) = delete;
	static UIManager* GetInstance();
	const std::map<std::string, TextInfo> GetCurrentTextsList();
	void AddText(const char* textName, const char* textContent,float posX, float posY, GameStateManager::GameState gameState, float renderScale = 1.0f);
	void UpdateText(const char* textName, const char* textContent, float posX, float posY, GameStateManager::GameState gameState);
	void Update();
	static float CenterTextXPos(size_t textLength, size_t screenWidth, float scale = 1.0f);
};

