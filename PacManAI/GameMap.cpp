#include "GameMap.h"
#include "GameConfig.h"
#include "AssetType.h"
#include "DefaultMaps.h"

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
		}
	}
	delete m_pMap;
}

void GameMap::loadMap(Character *pacman) {
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
				break;
			}
		}
	}

	pacman->setMap(this);
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