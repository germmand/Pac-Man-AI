#include "Character.h"

Character::Character(std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations) 
	: GameAsset(spritePath, renderer, spriteXAnimations, spriteYAnimations) {
	// El movimiento por defecto de cada Character será a la derecha.
	m_pDirection = new Movement();
	*m_pDirection = Movement::RIGHT;
}

Character::~Character() {
	delete m_pDirection;
}