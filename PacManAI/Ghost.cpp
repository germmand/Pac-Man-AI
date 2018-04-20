#include "Ghost.h"

Ghost::Ghost(Character *pacman, AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond) 
	: Character(type, spritePath, renderer, spriteXAnimations, spriteYAnimations, animationsPerSecond) {
	m_pPacman = pacman;
}

Ghost::~Ghost() {

}

void Ghost::moveCharacter(const int &FPS) {

}