#include "Ghost.h"
#include <iostream> // For debuggin' purposes only.

Ghost::Ghost(ANode *node, ANodeHandler *nodesHandler, Character *pacman, AssetType type, GameScreen *game, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond)
	: Character(node, game, type, spritePath, renderer, spriteXAnimations, spriteYAnimations, animationsPerSecond) {
	m_pPacman = pacman;
	m_pGame = game;
	m_pNodesHandler = nodesHandler;
}

Ghost::~Ghost() {

}

void Ghost::moveCharacter(const int &FPS) {
	GameAsset *collisionObject = nullptr;

	switch (*m_pDirection) {
	case Movement::RIGHT: {
			Character copiedCharacter = Character(m_dCurrentXPosition + 1, m_dCurrentYPosition, m_pMap);
			collisionObject = copiedCharacter.GetCollisionObject();

			if (collisionObject == nullptr || collisionObject->getType() != AssetType::WALL) {
				m_dCurrentXPosition < COLUMNS - 1 ? m_dCurrentXPosition += 1 : m_dCurrentXPosition = 0;
				m_dCurrentYAnimation = 0;
			}
		}
		break;
	case Movement::LEFT: {
			Character copiedCharacter = Character(m_dCurrentXPosition - 1, m_dCurrentYPosition, m_pMap);
			collisionObject = copiedCharacter.GetCollisionObject();

			if (collisionObject == nullptr || collisionObject->getType() != AssetType::WALL) {
				m_dCurrentXPosition > 0 ? m_dCurrentXPosition -= 1 : m_dCurrentXPosition = COLUMNS - 1;
				m_dCurrentYAnimation = 1;
			}
		}
		break;
	case Movement::UP: {
			Character copiedCharacter = Character(m_dCurrentXPosition, m_dCurrentYPosition - 1, m_pMap);
			collisionObject = copiedCharacter.GetCollisionObject();

			if (collisionObject == nullptr || collisionObject->getType() != AssetType::WALL) {
				m_dCurrentYPosition > 0 ? m_dCurrentYPosition -= 1 : m_dCurrentYPosition = ROWS - 1;
				m_dCurrentYAnimation = 2;
			}
		}
		break;
	case Movement::DOWN: {
			Character copiedCharacter = Character(m_dCurrentXPosition, m_dCurrentYPosition + 1, m_pMap);
			collisionObject = copiedCharacter.GetCollisionObject();

			if (collisionObject == nullptr || collisionObject->getType() != AssetType::WALL) {
				m_dCurrentYPosition < ROWS - 1 ? m_dCurrentYPosition += 1 : m_dCurrentYPosition = 0;
				m_dCurrentYAnimation = 3;
			}
		}
		break;
	}

	this->updatePosition(m_dCurrentXPosition, m_dCurrentYPosition);
	this->m_pCharacterNode->UpdateNode(m_dCurrentXPosition, m_dCurrentYPosition);

	if (hasEncounterPacman()) {
		//std::cout << "Pacman encountered!" << std::endl; // Para propositos de depuración.
		m_pGame->exitGame();
	}

	if (!m_pNodesHandler->SteppedOnANode(this->getANode())) {
		return;
	}

	//bool PathFound;
	//m_pNodesHandler->AStarAlgorithm(this->getANode(), m_pPacman->getANode(), &PathFound);

	//if (!PathFound) {
		std::vector<Movement> avalaiblePaths;
		determineAvalaiblePaths(&avalaiblePaths);

		if (avalaiblePaths.size() > 0) {
			*m_pDirection = avalaiblePaths[rand() % avalaiblePaths.size()];
		}

	//	return;
	//}

	//ComputeNextMovement();
}

void Ghost::ComputeNextMovement() {
	ANode *node;
	for (node = m_pPacman->getANode(); node->getParent()->getParent() != nullptr; node = node->getParent()) {
	}

	int x = node->getX() - this->getANode()->getX();
	int y = node->getY() - this->getANode()->getY();

	if (x > 0) *m_pDirection = Movement::RIGHT;
	else if (x < 0) *m_pDirection = Movement::LEFT;

	if (y > 0) *m_pDirection = Movement::DOWN;
	else if (y < 0) *m_pDirection = Movement::UP;
}

void Ghost::determineAvalaiblePaths(std::vector<Movement> *paths) {
	if (*m_pDirection != Movement::LEFT) {
		Character rightObject = Character(m_dCurrentXPosition + 1, m_dCurrentYPosition, m_pMap);
		addPath(&rightObject, paths, Movement::RIGHT);
	}

	if (*m_pDirection != Movement::RIGHT) {
		Character leftObject = Character(m_dCurrentXPosition - 1, m_dCurrentYPosition, m_pMap);
		addPath(&leftObject, paths, Movement::LEFT);
	}

	if (*m_pDirection != Movement::DOWN) {
		Character aboveObject = Character(m_dCurrentXPosition, m_dCurrentYPosition - 1, m_pMap);
		addPath(&aboveObject, paths, Movement::UP);
	}

	if (*m_pDirection != Movement::UP) {
		Character beneathObject = Character(m_dCurrentXPosition, m_dCurrentYPosition + 1, m_pMap);
		addPath(&beneathObject, paths, Movement::DOWN);
	}
}

void Ghost::addPath(Character *object, std::vector<Movement> *paths, Movement movement) {
	GameAsset *collisionObject = object->GetCollisionObject();

	if (collisionObject != nullptr && collisionObject->getType() != AssetType::WALL) {
		paths->push_back(movement);
	}
}

bool Ghost::hasEncounterPacman() {
	return (m_dCurrentXPosition == m_pPacman->getCurrentXPosition() && m_dCurrentYPosition == m_pPacman->getCurrentYPosition()) ||
		   (m_dCurrentXPosition - 1 == m_pPacman->getCurrentXPosition() && *m_pDirection == Movement::RIGHT && m_pPacman->getDirection() == Movement::LEFT && m_dCurrentYPosition == m_pPacman->getCurrentYPosition()) || 
		   (m_dCurrentXPosition + 1 == m_pPacman->getCurrentXPosition() && *m_pDirection == Movement::LEFT && m_pPacman->getDirection() == Movement::RIGHT && m_dCurrentYPosition == m_pPacman->getCurrentYPosition()) ||
		   (m_dCurrentYPosition - 1 == m_pPacman->getCurrentYPosition() && *m_pDirection == Movement::DOWN && m_pPacman->getDirection() == Movement::UP && m_dCurrentXPosition == m_pPacman->getCurrentXPosition()) || 
		   (m_dCurrentYPosition + 1 == m_pPacman->getCurrentYPosition() && *m_pDirection == Movement::UP && m_pPacman->getDirection() == Movement::DOWN && m_dCurrentXPosition == m_pPacman->getCurrentXPosition());
}