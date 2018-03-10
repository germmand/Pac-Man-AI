#pragma once

#include <SDL.h>
#include "GameAsset.h"

class GameScreen {
private:
	SDL_Window *m_pWindow;
	SDL_Renderer *m_pWindowRenderer;
	SDL_Event m_event;
	bool m_bIsRunning;

public:
	GameScreen();
	~GameScreen();
	SDL_Event *getEvent();
	SDL_Renderer *getRenderer();
	bool isRunning();
	void exitGame();
};