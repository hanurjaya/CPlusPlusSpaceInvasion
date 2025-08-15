#include "Player.h"

Player::Player(SDL_FRect* src, std::size_t screenWidth, std::size_t screenHeight, SDL_Texture* texture)
	: GameObject(src, new SDL_FRect{ (screenWidth / 2) - (src->w / 2), screenHeight - src->h, src->w, src->h }, texture, GameObject::ObjType::Player)
{

}

bool Player::GetIsPlayerShot()
{
	return m_isPlayerShot;
}

void Player::SetIsPlayerShot(bool isPlayerShot)
{
	m_isPlayerShot = isPlayerShot;
}

Player::~Player()
{
	delete[] m_src;
	delete[] m_dest;
	SDL_DestroyTexture(m_texture);
}
