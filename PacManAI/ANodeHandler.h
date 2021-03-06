#pragma once

#include <vector>
#include "ANode.h"
#include "GameMap.h"

class GameMap;

class ANodeHandler {
private:
	std::vector<ANode *> *m_pNodes;
	GameMap *m_pMap;
	
public:
	ANodeHandler();
	~ANodeHandler();
	void AddNode(ANode *nNode);
	std::vector<ANode *> FindNeighbors(ANode *node);
	void AStarAlgorithm(ANode *start, ANode *goal, bool *PathFound);
	void setMap(GameMap *map);

	bool SteppedOnANode(ANode *nNode);
private:
	ANode *FindNeighbor(ANode *node, int x, int y);

	ANode *FindLeftNeighbor(ANode *node);
	ANode *FindRightNeighbor(ANode *node);
	ANode *FindTopNeighbor(ANode *node);
	ANode *FindBottomNeighbor(ANode *node);

	ANode *FindLowestFNode(std::vector<ANode *> openSet);
	void EraseFromList(ANode *nNode, std::vector<ANode *> *nodeList);
	bool IsNodeOnList(ANode *nNode, std::vector<ANode *> *nodeList);
	bool IsNodeReachable(ANode *srcNode, ANode *destNode);
};