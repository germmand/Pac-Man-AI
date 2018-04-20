#include "GhostsHandler.h"

GhostsHandler::GhostsHandler() {
	m_pGhosts = new std::vector<Ghost *>();
}

GhostsHandler::~GhostsHandler() {
	for (size_t i = 0; i < m_pGhosts->size(); i++) {
		delete (*m_pGhosts)[i];
		(*m_pGhosts)[i] = nullptr;
	}

	delete m_pGhosts;
	m_pGhosts = nullptr;
}

std::vector<Ghost *> *GhostsHandler::getGhosts() {
	return m_pGhosts;
}