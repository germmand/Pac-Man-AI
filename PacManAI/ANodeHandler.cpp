#include "ANodeHandler.h"
#include "GameConfig.h"
#include <iostream>

ANodeHandler::ANodeHandler() {
	m_pNodes = new std::vector<ANode *>();
}

ANodeHandler::~ANodeHandler() {
	// Se libera la memoria.
	for (size_t i = 0; i < m_pNodes->size(); i++) {
		delete (*m_pNodes)[i];
		(*m_pNodes)[i] = nullptr;
	}

	delete m_pNodes;
	m_pNodes = nullptr;
}

void ANodeHandler::AddNode(ANode *nNode) {
	m_pNodes->push_back(nNode);
}

std::vector<ANode *> ANodeHandler::FindNeighbors(ANode *node) {
	std::vector<ANode *> neighbors;

	ANode *leftNeighbor = FindLeftNeighbor(node);
	if (leftNeighbor != nullptr) {
		neighbors.push_back(leftNeighbor);
	}

	ANode *rightNeighbor = FindRightNeighbor(node);
	if (rightNeighbor != nullptr) {
		neighbors.push_back(rightNeighbor);
	}

	ANode *topNeighbor = FindTopNeighbor(node);
	if (topNeighbor != nullptr) {
		neighbors.push_back(topNeighbor);
	}

	ANode *bottomNeighbor = FindBottomNeighbor(node);
	if (bottomNeighbor != nullptr) {
		neighbors.push_back(bottomNeighbor);
	}

	return neighbors;
}

ANode *ANodeHandler::FindNeighbor(ANode *node, int x, int y) {
	for (size_t i = 0; i < m_pNodes->size(); i++) {
		if ((*m_pNodes)[i]->getId() == node->getId()) {
			continue;
		}

		if ((*m_pNodes)[i]->getX() == x &&
			(*m_pNodes)[i]->getY() == y) {
			return (*m_pNodes)[i];
		}
	}

	return nullptr;
}

ANode *ANodeHandler::FindLeftNeighbor(ANode *node) {
	for (size_t i = 0; i < m_pNodes->size(); i++) {
		int leftX = node->getX() - i;
		if (leftX < 0) break;

		ANode *leftNeighbor = FindNeighbor(node, leftX, node->getY());

		if (leftNeighbor != nullptr) {
			return leftNeighbor;
		}
	}

	return nullptr;
}

ANode *ANodeHandler::FindRightNeighbor(ANode *node) {
	for (size_t i = 0; i < m_pNodes->size(); i++) {
		int rightX = node->getX() + i;
		if (rightX > WIDTH) break;

		ANode *rightNeighbor = FindNeighbor(node, rightX, node->getY());

		if (rightNeighbor != nullptr) {
			return rightNeighbor;
		}
	}

	return nullptr;
}

ANode *ANodeHandler::FindTopNeighbor(ANode *node) {
	for (size_t i = 0; i < m_pNodes->size(); i++) {
		int topY = node->getY() - i;
		if (topY < 0) break;

		ANode *topNeighbor = FindNeighbor(node, node->getX(), topY);

		if (topNeighbor != nullptr) {
			return topNeighbor;
		}
	}

	return nullptr;
}

ANode *ANodeHandler::FindBottomNeighbor(ANode *node) {
	for (size_t i = 0; i < m_pNodes->size(); i++) {
		int bottomY = node->getY() + i;
		if (bottomY > HEIGHT) break;

		ANode *bottomNeighbor = FindNeighbor(node, node->getX(), bottomY);

		if (bottomNeighbor != nullptr) {
			return bottomNeighbor;
		}
	}

	return nullptr;
}

void ANodeHandler::AStarAlgorithm(ANode *start, ANode *goal) {
	std::vector<ANode *> openSet;
	std::vector<ANode *> closedSet;

	start->setParent(nullptr);
	start->setG(0);
	start->setH(ANode::computeDistance(start, goal));
	start->setF(start->getG() + start->getH());
	openSet.push_back(start);

	while (openSet.size() > 0) {
		ANode *currentNode = FindLowestFNode(openSet);

		if (currentNode->getId() == goal->getId()) {
			// We reached the goal, do something.
			std::cout << "Goal reached!" << std::endl;
			return;
		}

		EraseFromList(currentNode, &openSet);
		closedSet.push_back(currentNode);

		std::vector<ANode *> currentNeighbors = FindNeighbors(currentNode);

		std::vector<ANode *>::iterator neighborIt;
		for (neighborIt = currentNeighbors.begin(); neighborIt != currentNeighbors.end(); neighborIt++) {
			ANode *neighbor = *neighborIt;

			if (IsNodeOnList(neighbor, &closedSet)) {
				continue;
			}

			if (!IsNodeOnList(neighbor, &openSet)) {
				openSet.push_back(neighbor);
			}

			int gScore = currentNode->getG() + ANode::computeDistance(currentNode, neighbor);
			int hScore = ANode::computeDistance(neighbor, goal);
			int fScore = gScore + hScore;

			if (fScore >= neighbor->getF()) {
				continue;
			}

			neighbor->setParent(currentNode);
			neighbor->setG(gScore);
			neighbor->setH(hScore);
			neighbor->setF(fScore);
		}
	}
}

ANode *ANodeHandler::FindLowestFNode(std::vector<ANode *> openSet) {
	ANode *lowestF = nullptr;

	for (size_t i = 0; i < openSet.size(); i++) {
		if (i == 0) {
			lowestF = openSet[i];
			continue;
		}

		if (openSet[i]->getF() < lowestF->getF()) {
			lowestF = openSet[i];
		}
	}

	return lowestF;
}

void ANodeHandler::EraseFromList(ANode *nNode, std::vector<ANode *> *nodeList) {
	for (size_t i = 0; i < nodeList->size(); i++) {
		if (nNode->getId() == (*nodeList)[i]->getId()) {
			nodeList->erase(nodeList->begin() + i);
			return;
		}
	}
}

bool ANodeHandler::IsNodeOnList(ANode *nNode, std::vector<ANode *> *nodeList) {
	for (size_t i = 0; i < nodeList->size(); i++) {
		if ((*nodeList)[i]->getId() == nNode->getId()) {
			return true;
		}
	}

	return false;
}