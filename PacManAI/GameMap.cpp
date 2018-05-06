#include "GameMap.h"
#include "GameConfig.h"
#include "AssetType.h"
#include "DefaultMaps.h"
#include "Ghost.h"
#include <iostream>
#include "ANode.h"
#include "NodeType.h"

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

void GameMap::loadMap(Character *pacman, GhostsHandler *ghostHandler, GameScreen *game, ANodeHandler *nodesHandler) {
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
				pacman->getANode()->UpdateNode(c, r);
				nodesHandler->AddNode(pacman->getANode());
				pacman->setMap(this);
				break;
			case 'o':
				delete (*m_pMap)[r][c];
				(*m_pMap)[r][c] = new GameAsset(AssetType::FOOD, "assets/food.bmp", m_pRenderer, 1, 1);
				(*m_pMap)[r][c]->updatePosition(c, r);
				game->increaseAmountOfFood();
				break;
			case 'O':
				delete (*m_pMap)[r][c];
				(*m_pMap)[r][c] = new GameAsset(AssetType::BOOSTFOOD, "assets/boostfood.bmp", m_pRenderer, 1, 1);
				(*m_pMap)[r][c]->updatePosition(c, r);
				game->increaseAmountOfFood();
				break;
			case 'A':
				ghostHandler->getGhosts()->push_back(new Ghost(new ANode(NodeType::GHOST_NODE, c, r, YELLOW_GHOST_ID), nodesHandler, pacman, AssetType::GHOST, game, "assets/ghost1.bmp", m_pRenderer, 1, 1));
				ghostHandler->getGhosts()->back()->updatePosition(c, r);
				nodesHandler->AddNode(ghostHandler->getGhosts()->back()->getANode());
				ghostHandler->getGhosts()->back()->setMap(this);
				ghostHandler->getGhosts()->back()->setDirection(Movement::LEFT);
				break;
			case 'B':
				ghostHandler->getGhosts()->push_back(new Ghost(new ANode(NodeType::GHOST_NODE, c, r, RED_GHOST_ID), nodesHandler, pacman, AssetType::GHOST, game, "assets/ghost2.bmp", m_pRenderer, 1, 1));
				ghostHandler->getGhosts()->back()->updatePosition(c, r);
				nodesHandler->AddNode(ghostHandler->getGhosts()->back()->getANode());
				ghostHandler->getGhosts()->back()->setMap(this);
				break;
			case 'D':
				ghostHandler->getGhosts()->push_back(new Ghost(new ANode(NodeType::GHOST_NODE, c, r, PINK_GHOST_ID), nodesHandler, pacman, AssetType::GHOST, game, "assets/ghost3.bmp", m_pRenderer, 1, 1));
				ghostHandler->getGhosts()->back()->updatePosition(c, r);
				nodesHandler->AddNode(ghostHandler->getGhosts()->back()->getANode());
				ghostHandler->getGhosts()->back()->setMap(this);
				break;
			case 'E':
				ghostHandler->getGhosts()->push_back(new Ghost(new ANode(NodeType::GHOST_NODE, c, r, BLUE_GHOST_ID), nodesHandler, pacman, AssetType::GHOST, game, "assets/ghost4.bmp", m_pRenderer, 1, 1));
				ghostHandler->getGhosts()->back()->updatePosition(c, r);
				nodesHandler->AddNode(ghostHandler->getGhosts()->back()->getANode());
				ghostHandler->getGhosts()->back()->setMap(this);
				break;
			}	

			int pathIntersections = 0;
			bool topIntersection	= false;
			bool bottomIntersection = false;
			bool rightIntersection	= false;
			bool leftIntersection	= false;

			if ((c - 1) >= 0 && map_one[r][c - 1] != 'X' && map_one[r][c] != 'X') {
				pathIntersections += 1;
				leftIntersection = true;
			}
			if ((c + 1) < COLUMNS && map_one[r][c + 1] != 'X' && map_one[r][c] != 'X') {
				pathIntersections += 1;
				rightIntersection = true;
			}
			if ((r - 1) >= 0 && map_one[r - 1][c] != 'X' && map_one[r][c] != 'X') {
				pathIntersections += 1;
				topIntersection = true;
			}
			if ((r + 1) < HEIGHT && map_one[r + 1][c] != 'X' && map_one[r][c] != 'X') {
				pathIntersections += 1;
				bottomIntersection = true;
			}

			if (pathIntersections >= 3 ||
				(pathIntersections == 2 && rightIntersection != leftIntersection) ||
				(pathIntersections == 2 && topIntersection != bottomIntersection)) {
				nodesHandler->AddNode(new ANode(NodeType::INTERSECTION_NODE, c, r, (r + 1) * (c + 1)));
			}
		}
	}

	ghostHandler->setNodesHandler(nodesHandler);
	nodesHandler->setMap(this);
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

AssetType GameMap::GetAssetTypeAt(int x, int y) {
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			if ((*m_pMap)[r][c] != nullptr					&&
				(*m_pMap)[r][c]->getCurrentXPosition() == x &&
				(*m_pMap)[r][c]->getCurrentYPosition() == y) {
				return (*m_pMap)[r][c]->getType();
			}
		}
	}

	return AssetType::NONE;
}