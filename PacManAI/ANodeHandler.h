#pragma once

#include <vector>
#include "ANode.h"

class ANodeHandler {
private:
	std::vector<ANode *> *m_pNodes;
	
public:
	ANodeHandler();
	~ANodeHandler();
	void AddNode(ANode *nNode);
	std::vector<ANode *> FindNeighbors(ANode *node);
	void AStarAlgorithm(ANode *start, ANode *goal);
private:
	ANode *FindNeighbor(ANode *node, int x, int y);

	ANode *FindLeftNeighbor(ANode *node);
	ANode *FindRightNeighbor(ANode *node);
	ANode *FindTopNeighbor(ANode *node);
	ANode *FindBottomNeighbor(ANode *node);

	ANode *FindLowestFNode(std::vector<ANode *> openSet);
	void EraseFromList(ANode *nNode, std::vector<ANode *> *nodeList);
	bool IsNodeOnList(ANode *nNode, std::vector<ANode *> *nodeList);
};