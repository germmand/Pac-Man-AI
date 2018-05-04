#pragma once

#include "GameAsset.h"
#include "Movement.h"
#include "GameConfig.h"
#include "AssetType.h"
#include "GameMap.h"
#include "GameScreen.h"
#include "ANode.h"

class GameMap;

class Character : public GameAsset {
protected:
	Movement *m_pDirection;
	GameMap *m_pMap;
	GameScreen *m_pGame;
	ANode *m_pCharacterNode;
	int m_dFrameCounter;
public:
	Character(ANode *node, GameScreen *game, AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond = DEFAULT_ANIMATIONS_PER_SECOND);
	Character(int xPosition, int yPosition, GameMap *map);
	~Character();
	GameAsset *GetCollisionObject();
	void setMap(GameMap *map);
	void setDirection(Movement direction);
	ANode *getANode();
	virtual void moveCharacter(const int &FPS);
};