#pragma once

#include <vector>
#include "Character.h"
#include "ANodeHandler.h"

class Character;

class GhostsHandler {
private:
	std::vector<Character *> *m_pGhosts;
	ANodeHandler *m_pANodesHandler;
public:
	GhostsHandler();
	~GhostsHandler();
	std::vector<Character *> *getGhosts();
	void renderGhosts();
	void moveGhosts(int fps);
	void setNodesHandler(ANodeHandler *nodesHandler);
};