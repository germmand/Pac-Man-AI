#pragma once

#include <SDL.h>
#include <string>

class GameAsset {
private:
	SDL_Rect *m_pRect;
	SDL_Texture *m_pTexture;
	SDL_Renderer *m_pRenderer;

public:
	GameAsset(const std::string& spritePath, SDL_Renderer *renderer, SDL_Rect *spriteRect = nullptr);
	~GameAsset();

	SDL_Texture *getSpriteTexture();
	SDL_Rect *getSpriteRect();

	void printAsset();
};