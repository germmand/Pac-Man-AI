#pragma once

#include <SDL.h>
#include "GameAsset.h"
#include <vector>
#include "Character.h"
#include "GhostsHandler.h"
#include "GameScreen.h"
#include "ANodeHandler.h"

class Character;
class GhostsHandler;
class ANodeHandler;

class GameMap {
private:
	SDL_Renderer *m_pRenderer;
	std::vector<std::vector<GameAsset *>> *m_pMap;
public:
	GameMap(SDL_Renderer *renderer);
	~GameMap();
	std::vector<std::vector<GameAsset *>> *getMap() const;
	void loadMap(Character *pacman, GhostsHandler *ghostHandler, GameScreen *game, ANodeHandler *nodesHandler);
	void renderMap();
	AssetType GetAssetTypeAt(int x, int y);
};