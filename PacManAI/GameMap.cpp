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

void GameMap::loadMap() {
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			if (map_one[r][c] == 'X') {
				delete (*m_pMap)[r][c];
				(*m_pMap)[r][c] = new GameAsset(AssetType::WALL, "assets/wall.bmp", m_pRenderer, 1, 1);
				(*m_pMap)[r][c]->updatePosition(r, c);
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