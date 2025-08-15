#include "GameStateManager.h"

GameStateManager* GameStateManager::m_gameStateManagerInstance = nullptr;

GameStateManager::GameStateManager()
	:m_currentState{ GameStateManager::Exit}
{

}

GameStateManager* GameStateManager::GetInstance()
{
	if (m_gameStateManagerInstance == nullptr)
	{
		m_gameStateManagerInstance = new GameStateManager();
	}
	return m_gameStateManagerInstance;
}

void GameStateManager::SetGameState(GameState gameState)
{
	m_currentState = gameState;
}

GameStateManager::GameState GameStateManager::GetGameState()
{
	return m_currentState;
}
