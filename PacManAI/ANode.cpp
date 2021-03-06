#include "ANode.h"
#include <math.h>

ANode::ANode(NodeType nType, int _x, int _y, int _id)
	: m_dX(_x), m_dY(_y), m_dId(_id){
	m_pType = new NodeType();
	*m_pType = nType;

	this->m_dG = 9999;
	this->m_dH = 9999;
	this->m_dF = this->m_dG + this->m_dH;
}

ANode::~ANode() {
	delete m_pType;
	m_pType = nullptr;
}

int ANode::computeDistance(ANode *src, ANode *dest) {
	return abs(src->m_dX - dest->m_dX) + abs(src->m_dY - dest->m_dY);
}

void ANode::setG(int g) {
	this->m_dG = g;
}

void ANode::setF(int f) {
	this->m_dF = f;
}

void ANode::setH(int h) {
	this->m_dH = h;
}

void ANode::setX(int x) {
	this->m_dX = x;
}

void ANode::setY(int y) {
	this->m_dY = y;
}

void ANode::setParent(ANode *parent) {
	this->m_pParent = parent;
}

int ANode::getG() {
	return this->m_dG;
}

int ANode::getF() {
	return this->m_dF;
}

int ANode::getH() {
	return this->m_dH;
}

int ANode::getId() {
	return this->m_dId;
}

int ANode::getX() {
	return this->m_dX;
}

int ANode::getY() {
	return this->m_dY;
}

ANode *ANode::getParent() {
	return this->m_pParent;
}

void ANode::UpdateNode(int x, int y) {
	this->m_dX = x;
	this->m_dY = y;
}

NodeType *ANode::getNodeType() {
	return this->m_pType;
}