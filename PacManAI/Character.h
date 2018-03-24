#pragma once

#include "GameAsset.h"
#include "Movement.h"
#include "GameConfig.h"
#include "AssetType.h"
#include "GameMap.h"

class GameMap;

class Character : public GameAsset {
private:
	Movement *m_pDirection;
	GameMap *m_pMap;
	int m_dFrameCounter;
public:
	Character(AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond = DEFAULT_ANIMATIONS_PER_SECOND);
	Character(int xPosition, int yPosition, GameMap *map);
	~Character();
	GameAsset *GetCollisionObject();
	void setMap(GameMap *map);
	void setDirection(Movement direction);
	void moveCharacter(const int& FPS);
};