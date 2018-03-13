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

	// Todos los assets tendr�n el mismo tama�o acorde al tama�o de la matriz.
	m_pPosition->w = WIDTH / COLUMNS;
	m_pPosition->h = HEIGHT / ROWS;

	// Se calcula el tama�o de cada Sprite en baso al tama�o de la textura y las animaciones dadas.
	m_pSprite->w = m_dSpriteWidth / m_dSpriteXAnimations;
	m_pSprite->h = m_dSpriteHeight / m_dSpriteYAnimations;

	// La animaci�n por defecto ser� la (0, 0).
	m_dCurrentXAnimation = m_dCurrentYAnimation = 0;
	this->updateSprite(m_dCurrentXAnimation, m_dCurrentYAnimation);

	// La posici�n por defecto ser� la (0, 0).
	m_dCurrentXPosition = m_dCurrentYPosition = 0;
	this->updatePosition(m_dCurrentXPosition, m_dCurrentYPosition);

	SDL_FreeSurface(surface);
}

GameAsset::~GameAsset() {
	delete m_pPosition;
	delete m_pSprite;

	SDL_DestroyTexture(m_pTexture);
}

void GameAsset::updatePosition(int x, int y) {
	m_dCurrentXPosition = x;
	m_dCurrentYPosition = y;

	m_pPosition->x = m_dCurrentXPosition * m_pPosition->w;
	m_pPosition->y = m_dCurrentYPosition * m_pPosition->h;
}

void GameAsset::updateSprite(int x, int y) {
	m_dCurrentXAnimation = x;
	m_dCurrentYAnimation = y;

	m_pSprite->x = m_dCurrentXAnimation * m_pSprite->w;
	m_pSprite->y = m_dCurrentYAnimation * m_pSprite->h;
}

void GameAsset::addToRenderer() {
	SDL_RenderCopy(m_pRenderer, m_pTexture, m_pSprite, m_pPosition);
}