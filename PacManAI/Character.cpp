#include "Character.h"
#include "ScreenConfig.h"

Character::Character(std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations) 
	: GameAsset(spritePath, renderer, spriteXAnimations, spriteYAnimations) {
	// El movimiento por defecto de cada Character será a la derecha.
	m_pDirection = new Movement();
	*m_pDirection = Movement::RIGHT;
}

Character::~Character() {
	delete m_pDirection;
}

void Character::setDirection(Movement direction) {
	*m_pDirection = direction;
}

void Character::moveCharacter() {
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

	this->updatePosition(m_dCurrentXPosition, m_dCurrentYPosition);
}