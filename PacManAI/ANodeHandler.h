#pragma once

#include <vector>
#include "ANode.h"

class ANodeHandler {
private:
	std::vector<ANode *> *m_pNodes;
	
public:
	ANodeHandler();
	~ANodeHandler();
};