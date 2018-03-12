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

	m_pWindowRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_bIsRunning = true;
	m_dFPS = 60;
	m_currentFrame = 0;
}

GameScreen::~GameScreen() {
	SDL_DestroyRenderer(m_pWindowRenderer);
	SDL_DestroyWindow(m_pWindow);
}

SDL_Event *GameScreen::getEvent() {
	return &m_event;
}

bool GameScreen::isRunning() {
	return m_bIsRunning;
}

void GameScreen::exitGame() {
	m_bIsRunning = false;
}

SDL_Renderer *GameScreen::getRenderer() {
	return m_pWindowRenderer;
}

void GameScreen::updateFrame() {
	m_currentFrame = (m_currentFrame + 1) % m_dFPS;
}

int *GameScreen::getCurrentFPSRate() {
	return &m_dFPS;
}

int *GameScreen::getCurrentFrameRate() {
	return &m_currentFrame;
}