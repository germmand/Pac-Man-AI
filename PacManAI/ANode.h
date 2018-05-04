#pragma once

#include "NodeType.h"

class ANode {
public:
	ANode(NodeType nType, int _x, int _y, int _id);
	~ANode();

	// Setters
	void setG(int g);
	void setF(int f);
	void setH(int h);
	void setX(int x);
	void setY(int y);
	void setParent(ANode *parent);

	// Getters
	int getG();
	int getF();
	int getH();
	int getId();
	int getX();
	int getY();
	ANode *getParent();
	NodeType *getNodeType();

	// Static method to compute the distance between two nodes.
	static int computeDistance(ANode *src, ANode *dst);

	void UpdateNode(int x, int y);
private:
	int m_dX, m_dY;
	int m_dF, m_dG, m_dH;
	int m_dId;
	NodeType *m_pType;
	ANode *m_pParent;
};