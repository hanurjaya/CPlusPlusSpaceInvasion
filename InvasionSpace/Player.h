#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
    bool m_isPlayerShot = false;
public:
    Player(SDL_FRect* src, std::size_t screenWidth, std::size_t screenHeight, SDL_Texture* texture);
    bool GetIsPlayerShot();
    void SetIsPlayerShot(bool isPlayerShot);
    ~Player();
};

