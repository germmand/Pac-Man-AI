#include "GameAsset.h"
#include <iostream>

GameAsset::GameAsset(const std::string& spritePath, SDL_Renderer *renderer, SDL_Rect *spriteRect) {
	SDL_Surface *surface = SDL_LoadBMP(spritePath.c_str());
	m_pRect = spriteRect;

	if (!surface) {
		std::cerr << "Error al cargar: " << spritePath << ", SDL Error: " << SDL_GetError() << std::endl;
	}

	m_pTexture = SDL_CreateTextureFromSurface(renderer, surface);
	m_pRenderer = renderer;
}

GameAsset::~GameAsset() {
	SDL_DestroyTexture(m_pTexture);
	delete m_pRect;
}

SDL_Texture *GameAsset::getSpriteTexture() {
	return m_pTexture;
}

SDL_Rect *GameAsset::getSpriteRect() {
	return m_pRect;
}

void GameAsset::printAsset() {
	SDL_RenderClear(m_pRenderer);
	SDL_RenderCopy(m_pRenderer, m_pTexture, nullptr, m_pRect);
	SDL_RenderPresent(m_pRenderer);
}