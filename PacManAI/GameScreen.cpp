#include "GameScreen.h"
#include "ScreenConfig.h"

GameScreen::GameScreen() {
	m_pWindow = SDL_CreateWindow(
					"Pac-Man AI", 
					SDL_WINDOWPOS_CENTERED, 
					SDL_WINDOWPOS_CENTERED, 
					WIDTH, 
					HEIGHT, 
					SDL_WINDOW_ALLOW_HIGHDPI);

	m_pWindowSurface = SDL_GetWindowSurface(m_pWindow);
	m_bIsRunning = true;
}

GameScreen::~GameScreen() {
	SDL_FreeSurface(m_pWindowSurface);
	SDL_DestroyWindow(m_pWindow);
}

SDL_Event *GameScreen::getEvent() {
	return &m_event;
}

void GameScreen::updateScreen() {
	SDL_UpdateWindowSurface(m_pWindow);
}

void GameScreen::paintAsset(GameAsset *asset) {
	SDL_BlitSurface(asset->getSpriteSurface(), asset->getSpriteRect(), m_pWindowSurface, nullptr);
}

bool GameScreen::isRunning() {
	return m_bIsRunning;
}

void GameScreen::exitGame() {
	m_bIsRunning = false;
}