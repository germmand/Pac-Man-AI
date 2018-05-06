#include "Character.h"
#include "GameConfig.h"

Character::Character(ANode *node, GameScreen *game, AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond)
	: GameAsset(type, spritePath, renderer, spriteXAnimations, spriteYAnimations, animationsPerSecond) {
	// El movimiento por defecto será el estático (al iniciar el juego, pac-man no se moverá).
	m_pDirection = new Movement();
	*m_pDirection = Movement::STATIC;
	m_pGame = game;
	m_pCharacterNode = node;

	m_dTotalPoints = 0;

	// Variable que se usará para determinar cuando ejecutar una animación
	// de acuerdo a los FPS y la variable animationsPerSecond.
	m_dFrameCounter = 0;
}

Character::~Character() {
	// No es necesario eliminar m_pCharacterNode de acá
	// ya que el manejador de nodos (ANodeHandler) 
	// Se encarga de ésta tarea.
	//delete m_pCharacterNode;

	delete m_pDirection;
	m_pDirection = nullptr;
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

int Character::getTotalPoints() {
	return this->m_dTotalPoints;
}

void Character::moveCharacter(const int &FPS) {
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

	if (collisionObject != nullptr && collisionObject->getCanRender() != false) {
		switch (collisionObject->getType()) {
		case AssetType::FOOD:
			collisionObject->setCanRender(false);
			m_pGame->decreaseAmountOfFood();
			m_dTotalPoints += 2;
			//collisionObject->setType(AssetType::NONE);
			break;
		case AssetType::BOOSTFOOD:
			collisionObject->setCanRender(false);
			m_pGame->decreaseAmountOfFood();
			m_dTotalPoints += 5;
			//collisionObject->setType(AssetType::NONE);
			break;
		}
	}

	if (m_pGame->getAmountOfGood() == 0) {
		m_pGame->setGameWon(true);
		m_pGame->exitGame();
	}

	m_dFrameCounter += 1;
	if (m_dFrameCounter == FPS / m_dAnimationsPerSecond) {
		m_dCurrentXAnimation = (m_dCurrentXAnimation + 1) % m_dSpriteXAnimations;
		m_dFrameCounter = 0;
	}

	this->updatePosition(m_dCurrentXPosition, m_dCurrentYPosition);
	this->m_pCharacterNode->UpdateNode(m_dCurrentXPosition, m_dCurrentYPosition);
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

ANode *Character::getANode() {
	return this->m_pCharacterNode;
}

void Character::SaveSpawnPosition(int x, int y) {
	m_dSpawnXPos = x;
	m_dSpawnYPos = y;
}

void Character::RestoreToSpawnPosition() {
	this->updatePosition(m_dSpawnXPos, m_dSpawnYPos);
	this->getANode()->UpdateNode(m_dSpawnXPos, m_dSpawnYPos);

	if (*this->m_pType == AssetType::PACMAN) {
		m_dCurrentXAnimation = 0;
		m_dCurrentYAnimation = 0;
		*m_pDirection = Movement::STATIC;
	}
}