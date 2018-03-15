#pragma once

#include <SDL.h>
#include "GameAsset.h"

class GameMap {
private:
	SDL_Renderer *m_pRenderer;
	GameAsset **m_pMap;
public:
	GameMap(SDL_Renderer *renderer);
	~GameMap();
};