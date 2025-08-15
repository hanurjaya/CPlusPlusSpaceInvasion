#pragma once
#include "GameObject.h"
class Projectile : public GameObject
{
	bool m_isFromPlayer{ false };
public:
	Projectile(SDL_FRect* src, float posX, float posY, bool isFromPlayer, SDL_Texture* texture);
	~Projectile();
	bool GetIsFromPlayer();
};

