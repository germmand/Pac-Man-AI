#pragma once

#include <vector>
#include "Ghost.h"

class GhostsHandler {
private:
	std::vector<Ghost *> *m_pGhosts;
public:
	GhostsHandler();
	~GhostsHandler();
	std::vector<Ghost *> *getGhosts();
};