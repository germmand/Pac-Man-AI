#pragma once

#include <SDL.h>
#include "GameAsset.h"

class GameScreen {
private:
	SDL_Window *m_pWindow;
	SDL_Surface *m_pWindowSurface;
	SDL_Event m_event;
	bool m_bIsRunning;

public:
	GameScreen();
	~GameScreen();
	SDL_Event *getEvent();
	void updateScreen();
	void paintAsset(GameAsset *asset);
	bool isRunning();
	void exitGame();
};