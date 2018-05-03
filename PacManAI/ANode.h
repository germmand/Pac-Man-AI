#pragma once

class ANode {
public:
	ANode(int _x, int _y, int _id);
	~ANode();

	// Setters
	void setG(int g);
	void setF(int f);
	void setH(int h);
	void setParent(ANode *parent);

	// Getters
	int getG();
	int getF();
	int getH();
	ANode *getParent();

	// Static method to compute the distance between two nodes.
	static int computeDistance(ANode *src, ANode *dst);
private:
	int m_dX, m_dY;
	int m_dF, m_dG, m_dH;
	int m_dId;
	ANode *m_pParent;
};