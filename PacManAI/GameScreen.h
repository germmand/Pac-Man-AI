#pragma once
#include <SDL.h>

class GameScreen {
private:
	SDL_Window *m_pWindow;
	SDL_Event m_event;
public:
	GameScreen();
	~GameScreen();
	SDL_Event *getEvent();
};