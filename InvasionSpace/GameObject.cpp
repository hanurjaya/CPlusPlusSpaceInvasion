#include "GameObject.h"

GameObject::GameObject(SDL_FRect* src, SDL_FRect* dest, SDL_Texture* texture, ObjType objType)
	: m_src{ src }
	, m_dest{ dest }
	, m_texture{ texture }
	, m_objType { objType }
{

}

SDL_FRect* GameObject::GetDestPos()
{
	return m_dest;
}

SDL_FRect* GameObject::GetSrcPos()
{
	return m_src;
}

SDL_Texture* GameObject::GetTexture()
{
	return m_texture;
}

GameObject::ObjType GameObject::GetObjType()
{
	return m_objType;
}

bool GameObject::GetIsActive()
{
	return m_isActive;
}

void GameObject::SetIsActive(bool isActive)
{
	m_isActive = isActive;
}