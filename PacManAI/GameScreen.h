#pragma once

#include <SDL.h>

class GameScreen {
private:
	SDL_Window *m_pWindow;
	SDL_Renderer *m_pWindowRenderer;
	SDL_Event m_event;
	bool m_bIsRunning;
	int m_dFPS;

public:
	GameScreen(int FPS = 10);
	~GameScreen();
	SDL_Event *getEvent();
	SDL_Renderer *getRenderer();
	bool isRunning();
	void exitGame();
	int getFPS();
};