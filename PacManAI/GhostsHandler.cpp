#include "GhostsHandler.h"
#include "GameConfig.h"

GhostsHandler::GhostsHandler() {
	m_pGhosts = new std::vector<Character *>();
}

GhostsHandler::~GhostsHandler() {
	for (size_t i = 0; i < m_pGhosts->size(); i++) {
		delete (*m_pGhosts)[i];
		(*m_pGhosts)[i] = nullptr;
	}

	delete m_pGhosts;
	m_pGhosts = nullptr;
}

std::vector<Character *> *GhostsHandler::getGhosts() {
	return m_pGhosts;
}

void GhostsHandler::renderGhosts() {
	std::vector<Character *>::iterator ghostsIterator;

	for (ghostsIterator = m_pGhosts->begin(); ghostsIterator != m_pGhosts->end(); ghostsIterator++) {
		(*ghostsIterator)->addToRenderer();
	}
}

void GhostsHandler::moveGhosts(int fps) {
	std::vector<Character *>::iterator ghostsIterator;

	for (ghostsIterator = m_pGhosts->begin(); ghostsIterator != m_pGhosts->end(); ghostsIterator++) {
		(*ghostsIterator)->moveCharacter(fps);
	}
}

void GhostsHandler::setNodesHandler(ANodeHandler *nodesHandler) {
	this->m_pANodesHandler = nodesHandler;
}

void GhostsHandler::restoreGhostsToSpawnPos() {
	std::vector<Character *>::iterator ghostsIterator;

	for (ghostsIterator = m_pGhosts->begin(); ghostsIterator != m_pGhosts->end(); ghostsIterator++) {
		(*ghostsIterator)->RestoreToSpawnPosition();
	}
}