#include "GameAsset.h"
#include "GameConfig.h"
#include <iostream>

GameAsset::GameAsset(AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond) {
	SDL_Surface *surface = SDL_LoadBMP(spritePath.c_str());
	if (!surface) {
		std::cerr << "Error al cargar: " << spritePath << ", Error:" << SDL_GetError() << std::endl;
	}

	m_pType = new AssetType();
	*m_pType = type;

	m_pRenderer = renderer;
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, surface);

	m_dAnimationsPerSecond = animationsPerSecond;

	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_dSpriteWidth, &m_dSpriteHeight);

	m_dSpriteXAnimations = spriteXAnimations;
	m_dSpriteYAnimations = spriteYAnimations;

	m_pPosition = new SDL_Rect();
	m_pSprite = new SDL_Rect();

	// Todos los assets tendrán el mismo tamaño acorde al tamaño de la matriz.
	m_pPosition->w = WIDTH / COLUMNS;
	m_pPosition->h = HEIGHT / ROWS;

	// Se calcula el tamaño de cada Sprite en baso al tamaño de la textura y las animaciones dadas.
	m_pSprite->w = m_dSpriteWidth / m_dSpriteXAnimations;
	m_pSprite->h = m_dSpriteHeight / m_dSpriteYAnimations;

	// La animación por defecto será la (0, 0).
	m_dCurrentXAnimation = m_dCurrentYAnimation = 0;
	this->updateSprite(m_dCurrentXAnimation, m_dCurrentYAnimation);

	// La posición por defecto será la (0, 0).
	m_dCurrentXPosition = m_dCurrentYPosition = 0;
	this->updatePosition(m_dCurrentXPosition, m_dCurrentYPosition);

	SDL_FreeSurface(surface);
}

GameAsset::GameAsset(AssetType type) {
	m_pType = new AssetType();
	*m_pType = type;
}

GameAsset::~GameAsset() {
	delete m_pPosition;
	delete m_pSprite;
	delete m_pType;

	SDL_DestroyTexture(m_pTexture);
}

AssetType GameAsset::getType() const {
	return *m_pType;
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

bool GameAsset::OnCollision(const GameAsset *asset) {
	return	(this->m_pPosition != nullptr && asset->m_pPosition != nullptr) &&
			asset->m_pPosition->x == this->m_pPosition->x					&&
			asset->m_pPosition->y == this->m_pPosition->y;
}