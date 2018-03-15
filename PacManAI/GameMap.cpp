#include "GameMap.h"
#include "GameConfig.h"
#include "AssetType.h"


GameMap::GameMap(SDL_Renderer *renderer) {
	m_pRenderer = renderer;

	// Se crea la matriz en memoria dinámica.
	m_pMap = new GameAsset*[ROWS];
	for (int r = 0; r < ROWS; r++) {
		m_pMap[r] = new GameAsset[COLUMNS];
	}

	// La matriz inicialmente estará vacía.
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			m_pMap[r][c] = GameAsset(AssetType::NONE);
		}
	}
}

GameMap::~GameMap() {
	// Se limpia la memoria.
	for (int r = 0; r < ROWS; r++) {
		delete[] m_pMap[r];
	}
	delete[] m_pMap;
}