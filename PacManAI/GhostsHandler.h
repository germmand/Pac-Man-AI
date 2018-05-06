#pragma once

#include <vector>
#include "Character.h"
#include "ANodeHandler.h"

class Character;
class ANodeHandler;

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
	void restoreGhostsToSpawnPos();
	void setNodesHandler(ANodeHandler *nodesHandler);
};