#pragma once

#include <SDL.h>
#include "GameAsset.h"
#include <vector>
#include "Character.h"
#include "GhostsHandler.h"
#include "GameScreen.h"

class Character;
class GhostsHandler;

class GameMap {
private:
	SDL_Renderer *m_pRenderer;
	std::vector<std::vector<GameAsset *>> *m_pMap;
public:
	GameMap(SDL_Renderer *renderer);
	~GameMap();
	std::vector<std::vector<GameAsset *>> *getMap() const;
	void loadMap(Character *pacman, GhostsHandler *ghostHandler, GameScreen *game);
	void renderMap();
};