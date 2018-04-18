#pragma once

#include <SDL.h>
#include <string>
#include "GameConfig.h"
#include "AssetType.h"

class GameAsset {
protected:
	SDL_Renderer *m_pRenderer;
	SDL_Texture *m_pTexture;
	SDL_Rect *m_pPosition, *m_pSprite;
	AssetType *m_pType;
	int m_dSpriteXAnimations, m_dSpriteYAnimations;
	int m_dSpriteWidth, m_dSpriteHeight;
	int m_dCurrentXAnimation, m_dCurrentYAnimation;
	int m_dCurrentXPosition, m_dCurrentYPosition;
	int m_dAnimationsPerSecond;

public:
	GameAsset(AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond = DEFAULT_ANIMATIONS_PER_SECOND);
	GameAsset(int xPosition, int yPosition);
	GameAsset(AssetType type);
	~GameAsset();
	void updatePosition(int x, int y);
	void updateSprite(int x, int y);
	void addToRenderer();
	AssetType getType() const;
	void setType(AssetType type) const;
	bool OnCollision(const GameAsset *asset);
};