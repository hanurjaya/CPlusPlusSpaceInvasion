#include "Enemy.h"

Enemy::Enemy(SDL_FRect* src, SDL_FRect* dest, SDL_Texture* texture, float scoreCount)
	: GameObject(src, dest, texture, GameObject::ObjType::Enemy)
	, m_scoreWeight{ scoreCount }
{

}

float Enemy::GetScoreWeight()
{
	return m_scoreWeight;
}

Enemy::~Enemy()
{
	delete[] m_src;
	delete[] m_dest;
	SDL_DestroyTexture(m_texture);
}
