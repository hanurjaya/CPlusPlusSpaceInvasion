#pragma once
#include <cstddef>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class GameObject
{
public:
	enum ObjType
	{
		Player,
		Enemy,
		Projectile,
		Unknown
	};
private:
	bool m_isActive = true;
	ObjType m_objType = ObjType::Unknown;
protected:
	SDL_FRect* m_src;
	SDL_FRect* m_dest;
	SDL_Texture* m_texture;
public:
	GameObject(SDL_FRect* src, SDL_FRect* dest, SDL_Texture* texture, ObjType objType);
	SDL_FRect* GetDestPos();
	SDL_FRect* GetSrcPos();
	SDL_Texture* GetTexture();
	ObjType GetObjType();
	bool GetIsActive();
	void SetIsActive(bool isActive);
	virtual ~GameObject() = default;
};

