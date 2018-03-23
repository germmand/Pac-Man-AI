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
	*m_pDirection = direction;
}

void Character::setMap(GameMap *map) {
	this->m_pMap = map;
}

void Character::moveCharacter(const int& FPS) {
	GameAsset *collisionObject = GetCollisionObject();
	if (collisionObject != nullptr) {
		switch (collisionObject->getType()) {
		case AssetType::WALL:
			if (*m_pDirection == Movement::RIGHT) m_dCurrentXPosition -= 1;
			else if (*m_pDirection == Movement::UP) m_dCurrentYPosition += 1;
			else if (*m_pDirection == Movement::LEFT) m_dCurrentXPosition += 1;
			else if (*m_pDirection == Movement::DOWN) m_dCurrentYPosition -= 1;

			*m_pDirection = Movement::STATIC;
			break;
		}
	}

	switch (*m_pDirection) {
	case Movement::RIGHT:
		m_dCurrentXPosition < COLUMNS - 1 ? m_dCurrentXPosition += 1 : m_dCurrentXPosition = 0;
		m_dCurrentYAnimation = 0;
		break;
	case Movement::UP:
		m_dCurrentYPosition > 0 ? m_dCurrentYPosition -= 1 : m_dCurrentYPosition = ROWS - 1;
		m_dCurrentYAnimation = 2;
		break;
	case Movement::LEFT:
		m_dCurrentXPosition > 0 ? m_dCurrentXPosition -= 1 : m_dCurrentXPosition = COLUMNS - 1;
		m_dCurrentYAnimation = 1;
		break;
	case Movement::DOWN:
		m_dCurrentYPosition < ROWS - 1 ? m_dCurrentYPosition += 1 : m_dCurrentYPosition = 0;
		m_dCurrentYAnimation = 3;
		break;
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