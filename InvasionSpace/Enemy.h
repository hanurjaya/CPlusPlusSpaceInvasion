#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
private:
	float m_scoreWeight{};
public:
	Enemy(SDL_FRect* src, SDL_FRect* dest, SDL_Texture* texture, float scoreCount);
	float GetScoreWeight();
	~Enemy();
};

