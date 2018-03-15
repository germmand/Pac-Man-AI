#pragma once

#include "GameAsset.h"
#include "Movement.h"
#include "GameConfig.h"
#include "AssetType.h"

class Character : public GameAsset {
private:
	Movement *m_pDirection;
	int m_dFrameCounter;
public:
	Character(AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond = DEFAULT_ANIMATIONS_PER_SECOND);
	~Character();
	void setDirection(Movement direction);
	void moveCharacter(const int& FPS);
};