#include "GameAsset.h"
#include <iostream>

GameAsset::GameAsset(const std::string& spritePath, SDL_Rect *spriteRect) {
	m_pSprite = SDL_LoadBMP(spritePath.c_str());
	m_pRect = spriteRect;

	if (!m_pSprite) {
		std::cerr << "Error al cargar: " << spritePath << ", SDL Error: " << SDL_GetError() << std::endl;
	}
}

GameAsset::~GameAsset() {
	SDL_FreeSurface(m_pSprite);

	delete m_pRect;
}

SDL_Surface *GameAsset::getSpriteSurface() {
	return m_pSprite;
}

SDL_Rect *GameAsset::getSpriteRect() {
	return m_pRect;
}