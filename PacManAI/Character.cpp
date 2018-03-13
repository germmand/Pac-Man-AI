#include "Character.h"
#include "GameConfig.h"

Character::Character(std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond) 
	: GameAsset(spritePath, renderer, spriteXAnimations, spriteYAnimations, animationsPerSecond) {
	// El movimiento por defecto de cada Character ser� a la derecha.
	m_pDirection = new Movement();
	*m_pDirection = Movement::RIGHT;

	// Variable que se usar� para determinar cuando ejecutar una animaci�n
	// de acuerdo a los FPS y la variable animationsPerSecond.
	m_dFrameCounter = 0;
}

Character::~Character() {
	delete m_pDirection;
}

void Character::setDirection(Movement direction) {
	*m_pDirection = direction;
}

void Character::moveCharacter(const int& FPS) {
	switch (*m_pDirection) {
	case Movement::RIGHT:
		if (m_dCurrentXPosition < COLUMNS - 1) {
			m_dCurrentXPosition += 1;
		}
		break;
	case Movement::UP:
		if (m_dCurrentYPosition > 0) {
			m_dCurrentYPosition -= 1;
		}
		break;
	case Movement::LEFT:
		if (m_dCurrentXPosition > 0) {
			m_dCurrentXPosition -= 1;
		}
		break;
	case Movement::DOWN:
		if (m_dCurrentYPosition < ROWS - 1) {
			m_dCurrentYPosition += 1;
		}
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