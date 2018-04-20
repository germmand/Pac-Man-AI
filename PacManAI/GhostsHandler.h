#pragma once

#include <vector>
#include "Character.h"

class Character;

class GhostsHandler {
private:
	std::vector<Character *> *m_pGhosts;
public:
	GhostsHandler();
	~GhostsHandler();
	std::vector<Character *> *getGhosts();
	void renderGhosts();
	void moveGhosts(int fps);
};