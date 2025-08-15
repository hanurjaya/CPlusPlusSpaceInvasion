#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::m_gameObjectManagerInstance = nullptr;

GameObjectManager::GameObjectManager()
	:m_needToRefreshList{true}
{

}

GameObjectManager* GameObjectManager::GetInstance()
{
	if (m_gameObjectManagerInstance == nullptr)
	{
		m_gameObjectManagerInstance = new GameObjectManager();
	}
	return m_gameObjectManagerInstance;
}

void GameObjectManager::SetRenderer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

void GameObjectManager::AddGameObject(GameObject* gameObject)
{
	m_gameObjectList.push_back(gameObject);
	RefreshLists();
}

std::vector<GameObject*> GameObjectManager::GetGameObjects()
{
	return m_gameObjectList;
}

void GameObjectManager::EnemyAIUpdate()
{
	if (GetElapsedTime() >= m_enemySPeed)
	{
		clock_start = std::chrono::system_clock::now();
		clock_now = std::chrono::system_clock::now();
		
		for (const auto& enemy : m_enemyObjectList)
		{
			if (enemy)
			{
				if (enemy->GetIsActive())
				{
					if (m_enemyNeedMoveDown)
					{
						enemy->GetDestPos()->y += enemy->GetDestPos()->h;
					}
					else if (m_isEnemyMoveLeft)
					{
						enemy->GetDestPos()->x -= 10.0f;
					}
					else
					{
						enemy->GetDestPos()->x += 10.0f;
					}
				}
			}
		}
		if (m_enemyNeedMoveDown)
		{
			m_enemyNeedMoveDown = false;
		}
	}
	else
	{
		clock_now = std::chrono::system_clock::now();
	}
}

void GameObjectManager::MovePlayer(bool isLeft)
{
	if (m_playerObject != nullptr)
	{
		if (isLeft)
		{
			if (m_playerObject->GetDestPos()->x > 30.0f)
			{
				m_playerObject->GetDestPos()->x -= 0.1f;
			}
		}
		else
		{
			if (m_playerObject->GetDestPos()->x + 60 < (m_width - 30))
			{
				m_playerObject->GetDestPos()->x += 0.1f;
			}
		}
	}
}

void GameObjectManager::DestroyGameObject(GameObject* gameObject)
{
	int index = 0;
	bool gameObjectFound = false;
	std::vector<GameObject*> tempContainer{};

	for (int i = 0; i < m_gameObjectList.size(); ++i)
	{
		if (m_gameObjectList[i] != gameObject)
		{
			tempContainer.push_back(m_gameObjectList[i]);
		}
	}
	delete gameObject;
	gameObject = nullptr;
	m_gameObjectList.clear();
	m_gameObjectList = tempContainer;
}

void GameObjectManager::DestroyAllGameObject()
{
	for (int i = 0; i < m_gameObjectList.size(); ++i)
	{
		delete m_gameObjectList[i];
	}
	m_gameObjectList.clear();
	m_enemyObjectList.clear();
	m_projectileObjectList.clear();
	m_playerObject = nullptr;
	m_isEnemyMoveLeft = true;
	m_enemyNeedMoveDown =false;
	m_totalScore = 0;
	m_enemySPeed = 1000.0f;
}

bool GameObjectManager::TrySpawnProjectileFromPlayer()
{
	if (m_playerObject != nullptr && !m_playerObject->GetIsPlayerShot())
	{
		float x = m_playerObject->GetDestPos()->x + (m_playerObject->GetDestPos()->w / 2) - ((8 / 2) / 2);
		float y = m_playerObject->GetDestPos()->y - (30 / 2);
		AddGameObject(new Projectile(new SDL_FRect{ 0, 0, 8, 30 }, x, y, true, IMG_LoadTexture(m_renderer, "projectile.png")));
		m_playerObject->SetIsPlayerShot(true);
		return true;
	}
	return false;
}

Player* GameObjectManager::GetPlayer()
{
	return m_playerObject;
}

bool GameObjectManager::IsNeedToRespawnEnemy()
{
	return m_enemyObjectList.size() <= 0;
}

void GameObjectManager::UpEnemySPeed()
{
	m_enemySPeed = 50.0f;
}

void GameObjectManager::DownEnemySPeed()
{
	m_enemySPeed += 1.0f;
}

int GameObjectManager::GetTotalScore()
{
	return m_totalScore;
}

void GameObjectManager::RefreshLists()
{
	m_enemyObjectList.clear();
	m_projectileObjectList.clear();
	m_playerObject = nullptr;
	for (const auto& gameObject : m_gameObjectList)
	{
		if (gameObject->GetObjType() == GameObject::Player)
		{
			m_playerObject = dynamic_cast<Player*>(gameObject);
		}
		else if (gameObject->GetObjType() == GameObject::Enemy)
		{
			m_enemyObjectList.push_back(dynamic_cast<Enemy*>(gameObject));
		}
		else if (gameObject->GetObjType() == GameObject::Projectile)
		{
			m_projectileObjectList.push_back(dynamic_cast<Projectile*>(gameObject));
		}
	}
}

void GameObjectManager::GetEnemyDirection()
{
	for (const auto& enemy : m_enemyObjectList)
	{
		if (enemy)
		{
			if (enemy->GetIsActive())
			{
				if (enemy->GetDestPos()->x < 30.0f && m_isEnemyMoveLeft)
				{
					m_isEnemyMoveLeft = false;
					m_enemyNeedMoveDown = true;
					break;
				}
				else if (enemy->GetDestPos()->x + enemy->GetDestPos()->w > m_width - 30 && !m_isEnemyMoveLeft)
				{
					m_isEnemyMoveLeft = true;
					m_enemyNeedMoveDown = true;
					break;
				}
			}
		}
	}
}

void GameObjectManager::Update()
{
	std::vector<GameObject*> tempContainer{};
	std::vector<GameObject*> inactiveContainer{};

	for (int i = 0; i < m_gameObjectList.size(); ++i)
	{
		if (m_gameObjectList[i]->GetIsActive())
		{
			tempContainer.push_back(m_gameObjectList[i]);
		}
		else
		{
			inactiveContainer.push_back(m_gameObjectList[i]);
		}
	}
	for (const auto& obj : inactiveContainer)
	{
		delete obj;
	}
	inactiveContainer.clear();
	m_gameObjectList.clear();
	m_gameObjectList = tempContainer;

	if (m_needToRefreshList)
	{
		RefreshLists();
	}
	if (m_enemyObjectList.size() <= 0)
	{
		if (m_enemySPeed > 210.0f)
		{
			m_enemySPeed -= 200.0f;
		}
		else if (m_enemySPeed < 210.0f && m_enemySPeed > 100.0f)
		{
			m_enemySPeed -= 50.0f;
		}
		m_isEnemyMoveLeft = true;
		m_enemyNeedMoveDown = false;
	}
	GetEnemyDirection();
	EnemyAIUpdate();
	ProjectilePosUpdate();
	CollisionUpdate();
}

void GameObjectManager::CollisionUpdate()
{
	for (const auto& projectile : m_projectileObjectList)
	{
		if (projectile->GetIsFromPlayer())
		{
			for (const auto& enemy : m_enemyObjectList)
			{
				if (projectile->GetIsActive() && enemy->GetIsActive() && checkCollision(projectile->GetDestPos(), enemy->GetDestPos()))
				{
					m_totalScore += enemy->GetScoreWeight();
					projectile->SetIsActive(false);
					enemy->SetIsActive(false);
					m_playerObject->SetIsPlayerShot(false);
				}
			}
		}
		else
		{
			if (m_playerObject != nullptr && m_playerObject->GetIsActive() && projectile->GetIsActive() && checkCollision(projectile->GetDestPos(), m_playerObject->GetDestPos()))
			{
				projectile->SetIsActive(false);
				m_playerObject->SetIsActive(false);
			}
		}
	}
	for (const auto& enemy : m_enemyObjectList)
	{
		if (m_playerObject != nullptr && m_playerObject->GetIsActive() && enemy->GetIsActive() && checkCollision(m_playerObject->GetDestPos(), enemy->GetDestPos()))
		{
			m_playerObject->SetIsActive(false);
		}
	}
}

void GameObjectManager::ProjectilePosUpdate()
{
	for (const auto& projectile : m_projectileObjectList)
	{
		if (projectile->GetIsFromPlayer())
		{
			if (projectile->GetDestPos()->y < 32)
			{
				projectile->SetIsActive(false);
				m_playerObject->SetIsPlayerShot(false);
			}
			else
			{
				projectile->GetDestPos()->y -= 0.05f;
			}
		}
		else
		{
			if (projectile->GetDestPos()->y > m_height)
			{
				projectile->SetIsActive(false);
			}
			else
			{
				projectile->GetDestPos()->y += 0.05f;
			}

		}
	}
}

float GameObjectManager::GetElapsedTime()
{
	return float(std::chrono::duration_cast <std::chrono::milliseconds> (clock_now - clock_start).count());
}

bool GameObjectManager::checkCollision(const SDL_FRect* a, const SDL_FRect* b)
{
	//The sides of the rectangles
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a->x;
	rightA = a->x + a->w;
	topA = a->y;
	bottomA = a->y + a->h;

	//Calculate the sides of rect B
	leftB = b->x;
	rightB = b->x + b->w;
	topB = b->y;
	bottomB = b->y + b->h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}


