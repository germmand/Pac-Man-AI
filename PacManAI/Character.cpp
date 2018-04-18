#include "Character.h"
#include "GameConfig.h"

Character::Character(AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond) 
	: GameAsset(type, spritePath, renderer, spriteXAnimations, spriteYAnimations, animationsPerSecond) {
	// El movimiento por defecto será el estático (al iniciar el juego, pac-man no se moverá).
	m_pDirection = new Movement();
	*m_pDirection = Movement::STATIC;

	// Variable que se usará para determinar cuando ejecutar una animación
	// de acuerdo a los FPS y la variable animationsPerSecond.
	m_dFrameCounter = 0;
}

Character::~Character() {
	delete m_pDirection;
}

void Character::setDirection(Movement direction) {
	Character *copiedCharacter = nullptr;

	switch (direction) {
	case Movement::RIGHT:
		copiedCharacter = new Character(m_dCurrentXPosition + 1, m_dCurrentYPosition, m_pMap);
		break;
	case Movement::UP:
		copiedCharacter = new Character(m_dCurrentXPosition, m_dCurrentYPosition - 1, m_pMap);
		break;
	case Movement::LEFT: 
		copiedCharacter = new Character(m_dCurrentXPosition - 1, m_dCurrentYPosition, m_pMap);
		break;
	case Movement::DOWN:
		copiedCharacter = new Character(m_dCurrentXPosition, m_dCurrentYPosition + 1, m_pMap);
		break;
	}

	// Se verifica que en la dirección en la que se vaya a mover no esté un muro.
	// Si hay un muro, no cambia de dirección, sino que se sigue movimiendo en la dirección que lo hacía.
	GameAsset *collisionObject = copiedCharacter->GetCollisionObject();
	if (collisionObject == nullptr || collisionObject->getType() != AssetType::WALL) {
		*m_pDirection = direction;
	}

	delete copiedCharacter;
}

void Character::setMap(GameMap *map) {
	this->m_pMap = map;
}

void Character::moveCharacter(const int& FPS) {
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
		case Movement::UP: {
			Character copiedCharacter = Character(m_dCurrentXPosition, m_dCurrentYPosition - 1, m_pMap);
			collisionObject = copiedCharacter.GetCollisionObject();

			if (collisionObject == nullptr || collisionObject->getType() != AssetType::WALL) {
				m_dCurrentYPosition > 0 ? m_dCurrentYPosition -= 1 : m_dCurrentYPosition = ROWS - 1;
				m_dCurrentYAnimation = 2;
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

	if (collisionObject != nullptr) {
		switch (collisionObject->getType()) {
		case AssetType::FOOD:
			collisionObject->updatePosition(-1, -1);
			collisionObject->setType(AssetType::NONE);
			break;
		}
	}

	m_dFrameCounter += 1;
	if (m_dFrameCounter == FPS / m_dAnimationsPerSecond) {
		m_dCurrentXAnimation = (m_dCurrentXAnimation + 1) % m_dSpriteXAnimations;
		m_dFrameCounter = 0;
	}

	this->updatePosition(m_dCurrentXPosition, m_dCurrentYPosition);
	this->updateSprite(m_dCurrentXAnimation, m_dCurrentYAnimation);
}

GameAsset *Character::GetCollisionObject() {
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			if ((*(m_pMap->getMap()))[r][c]->OnCollision(this) && (*(m_pMap->getMap()))[r][c]->getType() != AssetType::NONE) {
				return (*(m_pMap->getMap()))[r][c];
			}
		}
	}

	return nullptr;
}

Character::Character(int xPosition, int yPosition, GameMap *map)
	: GameAsset(xPosition, yPosition) {
	m_pMap = map;
}