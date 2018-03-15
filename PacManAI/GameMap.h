#pragma once

#include <SDL.h>

class GameMap {
private:
	SDL_Renderer *m_pRenderer;
	int **m_pMap;
public:
	GameMap(SDL_Renderer *renderer);
	~GameMap();
};