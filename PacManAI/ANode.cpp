#include "ANode.h"
#include <math.h>

ANode::ANode(int _x, int _y, int _id) 
	: m_dX(_x), m_dY(_y), m_dId(_id){
}

ANode::~ANode() {
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

ANode *ANode::getParent() {
	return this->m_pParent;
}