#include "GameMap.h"
#include "GameConfig.h"
#include "AssetType.h"
#include "DefaultMaps.h"
#include "Ghost.h"

GameMap::GameMap(SDL_Renderer *renderer) {
	m_pRenderer = renderer;

	// Se inicializa la matrix vacía.
	m_pMap = new std::vector<std::vector<GameAsset *>>();
	for (int r = 0; r < ROWS; r++) {
		std::vector<GameAsset *> vRows;
		for (int c = 0; c < COLUMNS; c++) {
			vRows.push_back(new GameAsset(AssetType::NONE));
		}
		m_pMap->push_back(vRows);
	}
}

GameMap::~GameMap() {
	// Se limpia la memoria.
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			delete (*m_pMap)[r][c];
			(*m_pMap)[r][c] = nullptr;
		}
	}
	delete m_pMap;
	m_pMap = nullptr;
}

void GameMap::loadMap(Character *pacman, GhostsHandler *ghostHandler) {
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			switch (map_one[r][c]) {
			case 'X':
				delete (*m_pMap)[r][c];
				(*m_pMap)[r][c] = new GameAsset(AssetType::WALL, "assets/wall.bmp", m_pRenderer, 1, 1);
				(*m_pMap)[r][c]->updatePosition(c, r);
				break;
			case 'C':
				pacman->updatePosition(c, r);
				pacman->setMap(this);
				break;
			case 'o':
				delete (*m_pMap)[r][c];
				(*m_pMap)[r][c] = new GameAsset(AssetType::FOOD, "assets/food.bmp", m_pRenderer, 1, 1);
				(*m_pMap)[r][c]->updatePosition(c, r);
				break;
			case 'O':
				delete (*m_pMap)[r][c];
				(*m_pMap)[r][c] = new GameAsset(AssetType::BOOSTFOOD, "assets/boostfood.bmp", m_pRenderer, 1, 1);
				(*m_pMap)[r][c]->updatePosition(c, r);
				break;
			case 'A':
				ghostHandler->getGhosts()->push_back(new Ghost(pacman, AssetType::GHOST, "assets/ghost1.bmp", m_pRenderer, 1, 1));
				ghostHandler->getGhosts()->back()->updatePosition(c, r);
				ghostHandler->getGhosts()->back()->setMap(this);
				ghostHandler->getGhosts()->back()->setDirection(Movement::LEFT);
				break;
			case 'B':
				ghostHandler->getGhosts()->push_back(new Ghost(pacman, AssetType::GHOST, "assets/ghost2.bmp", m_pRenderer, 1, 1));
				ghostHandler->getGhosts()->back()->updatePosition(c, r);
				ghostHandler->getGhosts()->back()->setMap(this);
				break;
			case 'D':
				ghostHandler->getGhosts()->push_back(new Ghost(pacman, AssetType::GHOST, "assets/ghost3.bmp", m_pRenderer, 1, 1));
				ghostHandler->getGhosts()->back()->updatePosition(c, r);
				ghostHandler->getGhosts()->back()->setMap(this);
				break;
			case 'E':
				ghostHandler->getGhosts()->push_back(new Ghost(pacman, AssetType::GHOST, "assets/ghost4.bmp", m_pRenderer, 1, 1));
				ghostHandler->getGhosts()->back()->updatePosition(c, r);
				ghostHandler->getGhosts()->back()->setMap(this);
				break;
			}	
		}
	}
}

void GameMap::renderMap() {
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			(*m_pMap)[r][c]->addToRenderer();
		}
	}
}

std::vector<std::vector<GameAsset *>> *GameMap::getMap() const {
	return m_pMap;
}