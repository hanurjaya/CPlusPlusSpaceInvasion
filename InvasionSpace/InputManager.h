#pragma once
#include <SDL3/SDL.h>
#include "GameStateManager.h"
#include "GameObjectManager.h"
#include "Constant.h"

class InputManager
{
private:
	static InputManager* m_InputManagerInstance;
	const bool* keyboardState = nullptr;
	InputManager();
	const bool* GetKeyboardState();
public:
	InputManager(InputManager&) = delete;
	void operator=(const InputManager&) = delete;
	static InputManager* GetInstance();
	void Update();
};

