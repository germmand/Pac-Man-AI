#pragma once

#include <SDL.h>
#include <string>

class GameAsset {
protected:
	SDL_Renderer *m_pRenderer;
	SDL_Texture *m_pTexture;
	SDL_Rect *m_pPosition, *m_pSprite;
	int m_dSpriteXAnimations, m_dSpriteYAnimations;

public:
	GameAsset(std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations);
	~GameAsset();
};