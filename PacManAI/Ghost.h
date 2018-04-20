#pragma once

#include "Character.h"
#include "AssetType.h"
#include "GameConfig.h"

class Ghost : public Character {
public:
	Ghost(AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond = DEFAULT_ANIMATIONS_PER_SECOND);
	~Ghost();
	void moveCharacter(const int &FPS);
};