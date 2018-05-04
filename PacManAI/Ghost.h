#pragma once

#include "Character.h"
#include "AssetType.h"
#include "GameConfig.h"
#include <vector>
#include "GameScreen.h"
#include "ANodeHandler.h"

class Ghost : public Character {
private:
	Character *m_pPacman;
	ANodeHandler *m_pNodesHandler;

public:
	Ghost(ANodeHandler *nodesHandler, Character *pacman, AssetType type, GameScreen *game, std::string spritePath, SDL_Renderer *renderer, int spriteXAnimations, int spriteYAnimations, int animationsPerSecond = DEFAULT_ANIMATIONS_PER_SECOND);
	~Ghost();
	void moveCharacter(const int &FPS);

private:
	void determineAvalaiblePaths(std::vector<Movement> *paths);
	void addPath(Character *object, std::vector<Movement> *paths, Movement movement);
	bool hasEncounterPacman();
};