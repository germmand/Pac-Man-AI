#include "Character.h"
#include "GameConfig.h"

Character::Character(AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond) 
	: GameAsset(type, spritePath, renderer, spriteXAnimations, spriteYAnimations, animationsPerSecond) {
	// El movimiento por defecto de cada Character será a la derecha.
	m_pDirection = new Movement();
	*m_pDirection = Movement::RIGHT;

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
	switch (*m_pDirection) {
	case Movement::RIGHT:
		m_dCurrentXPosition < COLUMNS - 1 ? m_dCurrentXPosition += 1 : m_dCurrentXPosition = 0;
		break;
	case Movement::UP:
		m_dCurrentYPosition > 0 ? m_dCurrentYPosition -= 1 : m_dCurrentYPosition = ROWS - 1;
		break;
	case Movement::LEFT:
		m_dCurrentXPosition > 0 ? m_dCurrentXPosition -= 1 : m_dCurrentXPosition = COLUMNS - 1;
		break;
	case Movement::DOWN:
		m_dCurrentYPosition < ROWS - 1 ? m_dCurrentYPosition += 1 : m_dCurrentYPosition = 0;
		break;
	}

	m_dCurrentYAnimation = *m_pDirection - 1;

	m_dFrameCounter += 1;
	if (m_dFrameCounter == FPS / m_dAnimationsPerSecond) {
		m_dCurrentXAnimation = (m_dCurrentXAnimation + 1) % m_dSpriteXAnimations;
		m_dFrameCounter = 0;
	}

	this->updatePosition(m_dCurrentXPosition, m_dCurrentYPosition);
	this->updateSprite(m_dCurrentXAnimation, m_dCurrentYAnimation);
}