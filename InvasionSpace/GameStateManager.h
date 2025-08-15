#pragma once
class GameStateManager
{
public:
	enum GameState
	{
		StartMenu,
		InGame,
		GameOver,
		Exit
	};
private:
	GameState m_currentState = Exit;
	static GameStateManager* m_gameStateManagerInstance;
	GameStateManager();
public:
	GameStateManager(GameStateManager&) = delete;
	void operator=(const GameStateManager&) = delete;
	static GameStateManager* GetInstance();
	void SetGameState(GameState gameState);
	GameState GetGameState();
};


