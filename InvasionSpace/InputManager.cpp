#include "InputManager.h"

InputManager* InputManager::m_InputManagerInstance = nullptr;

InputManager::InputManager()
{

}

InputManager* InputManager::GetInstance()
{
	if (m_InputManagerInstance == nullptr)
	{
		m_InputManagerInstance = new InputManager();
	}
	return m_InputManagerInstance;
}

const bool* InputManager::GetKeyboardState()
{
	return SDL_GetKeyboardState(NULL);
}

void InputManager::Update()
{
	SDL_Event sdl_event;
	SDL_PollEvent(&sdl_event);

	keyboardState = GetKeyboardState();

	if (sdl_event.type == SDL_EVENT_QUIT)
	{
		GameStateManager::GetInstance()->SetGameState(GameStateManager::Exit);
	}

	if (GameStateManager::GetInstance()->GetGameState() == GameStateManager::StartMenu)
	{
		if (keyboardState[SDL_SCANCODE_ESCAPE] || sdl_event.type == SDL_EVENT_QUIT)
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::Exit);
		}
        if (keyboardState[SDL_SCANCODE_RETURN])
        {
            GameStateManager::GetInstance()->SetGameState(GameStateManager::InGame);
        }
	}
	else if (GameStateManager::GetInstance()->GetGameState() == GameStateManager::InGame)
	{
		if (GameObjectManager::GetInstance()->GetPlayer() == nullptr)
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameOver);
		}
		if (keyboardState[SDL_SCANCODE_W])
		{
		}
		if (keyboardState[SDL_SCANCODE_A])
		{
			GameObjectManager::GetInstance()->MovePlayer(true);
		}
		if (keyboardState[SDL_SCANCODE_S])
		{
		}
		if (keyboardState[SDL_SCANCODE_D])
		{
			GameObjectManager::GetInstance()->MovePlayer(false);
		}
		if (keyboardState[SDL_SCANCODE_SPACE])
		{
			GameObjectManager::GetInstance()->TrySpawnProjectileFromPlayer();
		}
		if (keyboardState[SDL_SCANCODE_F])
		{
			GameObjectManager::GetInstance()->UpEnemySPeed();
		}
		if (keyboardState[SDL_SCANCODE_V])
		{
			GameObjectManager::GetInstance()->DownEnemySPeed();
		}
	}
	else if (GameStateManager::GetInstance()->GetGameState() == GameStateManager::GameOver)
	{
		if (keyboardState[SDL_SCANCODE_Y])
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::InGame);
		}
		if (keyboardState[SDL_SCANCODE_N])
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::Exit);
		}
	}
}
