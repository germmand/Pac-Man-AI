#include "Ghost.h"

Ghost::Ghost(AssetType type, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond) 
	: Character(type, spritePath, renderer, spriteXAnimations, spriteYAnimations, animationsPerSecond) {

}

Ghost::~Ghost() {

}

void Ghost::moveCharacter(const int &FPS) {

}