#include "Projectile.h"

Projectile::Projectile(SDL_FRect* src, float posX, float posY, bool isFromPlayer, SDL_Texture* texture)
	: m_isFromPlayer{isFromPlayer},
	GameObject(src, new SDL_FRect{ posX, posY, src->w / 2, src->h / 2}, texture, GameObject::ObjType::Projectile)
{

}

Projectile::~Projectile()
{
	delete[] m_src;
	delete[] m_dest;
	SDL_DestroyTexture(m_texture);
}

bool Projectile::GetIsFromPlayer()
{
	return m_isFromPlayer;
}
