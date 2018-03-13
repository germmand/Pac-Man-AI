#pragma once

#include "GameAsset.h"
#include "Movement.h"

class Character : public GameAsset {
private:
	Movement *m_pDirection;
public:
	Character(std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations);
	~Character();
	void setDirection(Movement direction);
	void moveCharacter();
};