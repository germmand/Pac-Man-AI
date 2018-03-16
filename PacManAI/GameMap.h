#pragma once

#include <SDL.h>
#include "GameAsset.h"
#include <vector>

class GameMap {
private:
	SDL_Renderer *m_pRenderer;
	std::vector<std::vector<GameAsset *>> *m_pMap;
public:
	GameMap(SDL_Renderer *renderer);
	~GameMap();
	void loadMap();
	void renderMap();
};