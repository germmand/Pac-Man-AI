#pragma once

#include <SDL.h>
#include <string>

class GameAsset {
private:
	SDL_Surface *m_pSprite;
	SDL_Rect *m_pRect;

public:
	GameAsset(const std::string& spritePath, SDL_Rect *spriteRect = nullptr);
	~GameAsset();

	SDL_Surface *getSpriteSurface();
	SDL_Rect *getSpriteRect();
};