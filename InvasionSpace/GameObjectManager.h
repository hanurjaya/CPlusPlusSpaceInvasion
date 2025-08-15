#pragma once
#include <vector>
#include <chrono>
#include <iostream>
#include "GameObject.h"
#include "Constant.h"
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"

class GameObjectManager
{
private:
	SDL_Renderer* m_renderer = nullptr;
	std::vector<GameObject*> m_gameObjectList{};
	std::vector<Enemy*> m_enemyObjectList{};
	std::vector<Projectile*> m_projectileObjectList{};
	bool m_needToRefreshList{ true };
	bool m_isEnemyMoveLeft{ true };
	bool m_enemyNeedMoveDown{ false };
	float m_enemySPeed{ 1000.0f };
	int m_totalScore{ 0 };
	float m_projectileSpeed{200.0f};
	float m_playerSpeed{30000.0f};
	Uint64 clock_start{ SDL_GetTicks() };
	Uint64 clock_now{ SDL_GetTicks() };
	Uint64 m_sdlTicks{ SDL_GetTicksNS() };
	Player* m_playerObject{};
	GameObjectManager();
	static GameObjectManager* m_gameObjectManagerInstance;
	void RefreshLists();
	void GetEnemyDirection();
	void EnemyAIUpdate();
	void CollisionUpdate();
	void ProjectilePosUpdate();
	Uint64 GetElapsedTime();
	bool checkCollision(const SDL_FRect* a, const SDL_FRect* b);
public:
	GameObjectManager(GameObjectManager&) = delete;
	void operator=(const GameObjectManager&) = delete;
	static GameObjectManager* GetInstance();
	void SetRenderer(SDL_Renderer* renderer);
	void AddGameObject(GameObject* gameObject);
	std::vector<GameObject*> GetGameObjects();
	void MovePlayer(bool isLeft);
	void DestroyGameObject(GameObject* gameObject);
	void DestroyAllGameObject();
	bool TrySpawnProjectileFromPlayer();
	Player* GetPlayer();
	bool IsNeedToRespawnEnemy();
	void UpEnemySPeed();
	void DownEnemySPeed();
	int GetTotalScore();
	void Update();
};

