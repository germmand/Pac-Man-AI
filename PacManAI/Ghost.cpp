#include "Ghost.h"
#include <iostream>

Ghost::Ghost(Character *pacman, AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond) 
	: Character(type, spritePath, renderer, spriteXAnimations, spriteYAnimations, animationsPerSecond) {
	m_pPacman = pacman;
}

Ghost::~Ghost() {

}

void Ghost::moveCharacter(const int &FPS) {
	GameAsset *collisionObject = nullptr;
	bool hasToSwitchPath = false;

	switch (*m_pDirection) {
	case Movement::RIGHT: {
			Character copiedCharacter = Character(m_dCurrentXPosition + 1, m_dCurrentYPosition, m_pMap);
			collisionObject = copiedCharacter.GetCollisionObject();

			if (collisionObject == nullptr || collisionObject->getType() != AssetType::WALL) {
				m_dCurrentXPosition < COLUMNS - 1 ? m_dCurrentXPosition += 1 : m_dCurrentXPosition = 0;
				m_dCurrentYAnimation = 0;
			} else {
				hasToSwitchPath = true;
			}
		}
		break;
	case Movement::LEFT: {
			Character copiedCharacter = Character(m_dCurrentXPosition - 1, m_dCurrentYPosition, m_pMap);
			collisionObject = copiedCharacter.GetCollisionObject();

			if (collisionObject == nullptr || collisionObject->getType() != AssetType::WALL) {
				m_dCurrentXPosition > 0 ? m_dCurrentXPosition -= 1 : m_dCurrentXPosition = COLUMNS - 1;
				m_dCurrentYAnimation = 1;
			} else {
				hasToSwitchPath = true;
			}
		}
		break;
	case Movement::UP: {
			Character copiedCharacter = Character(m_dCurrentXPosition, m_dCurrentYPosition - 1, m_pMap);
			collisionObject = copiedCharacter.GetCollisionObject();

			if (collisionObject == nullptr || collisionObject->getType() != AssetType::WALL) {
				m_dCurrentYPosition > 0 ? m_dCurrentYPosition -= 1 : m_dCurrentYPosition = ROWS - 1;
				m_dCurrentYAnimation = 2;
			} else {
				hasToSwitchPath = true;
			}
		}
		break;
	case Movement::DOWN: {
			Character copiedCharacter = Character(m_dCurrentXPosition, m_dCurrentYPosition + 1, m_pMap);
			collisionObject = copiedCharacter.GetCollisionObject();

			if (collisionObject == nullptr || collisionObject->getType() != AssetType::WALL) {
				m_dCurrentYPosition < ROWS - 1 ? m_dCurrentYPosition += 1 : m_dCurrentYPosition = 0;
				m_dCurrentYAnimation = 3;
			} else {
				hasToSwitchPath = true;
			}
		}
		break;
	}

	if (!hasToSwitchPath) {
		this->updatePosition(m_dCurrentXPosition, m_dCurrentYPosition);
		return;
	}

	// HERE WILL GO THE ALGORITHM TO TRACK PACMAN...
	std::vector<Movement> avalaiblePaths;
	determineAvalaiblePaths(&avalaiblePaths);
}

void Ghost::determineAvalaiblePaths(std::vector<Movement> *paths) {
	Character rightObject = Character(m_dCurrentXPosition + 1, m_dCurrentYPosition, m_pMap);
	addPath(&rightObject, paths, Movement::RIGHT);

	Character leftObject = Character(m_dCurrentXPosition - 1, m_dCurrentYPosition, m_pMap);
	addPath(&leftObject, paths, Movement::LEFT);

	Character aboveObject = Character(m_dCurrentXPosition, m_dCurrentYPosition - 1, m_pMap);
	addPath(&aboveObject, paths, Movement::UP);

	Character beneathObject = Character(m_dCurrentXPosition, m_dCurrentYPosition + 1, m_pMap);
	addPath(&beneathObject, paths, Movement::DOWN);
}

void Ghost::addPath(Character *object, std::vector<Movement> *paths, Movement movement) {
	GameAsset *collisionObject = object->GetCollisionObject();

	if (collisionObject != nullptr && collisionObject->getType() != AssetType::WALL) {
		paths->push_back(movement);
	}
}