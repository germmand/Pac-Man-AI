#include "GameAsset.h"
#include "ScreenConfig.h"
#include <iostream>

GameAsset::GameAsset(std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations) {
	SDL_Surface *surface = SDL_LoadBMP(spritePath.c_str());
	if (!surface) {
		std::cerr << "Error al cargar: " << spritePath << ", Error:" << SDL_GetError() << std::endl;
	}

	m_pRenderer = renderer;
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, surface);

	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_dSpriteWidth, &m_dSpriteHeight);

	m_dSpriteXAnimations = spriteXAnimations;
	m_dSpriteYAnimations = spriteYAnimations;

	m_pPosition = new SDL_Rect();
	m_pSprite = new SDL_Rect();

	// Todos los assets tendrán el mismo tamaño acorde al tamaño de la matriz.
	m_pPosition->w = WIDTH / COLUMNS;
	m_pPosition->h = HEIGHT / ROWS;

	// La animación por defecto será la (0, 0).
	m_dCurrentXAnimation = m_dCurrentYAnimation = 0;

	SDL_FreeSurface(surface);
}

GameAsset::~GameAsset() {
	delete m_pPosition;
	delete m_pSprite;

	SDL_DestroyTexture(m_pTexture);
}