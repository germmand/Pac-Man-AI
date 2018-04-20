#include "GhostsHandler.h"

GhostsHandler::GhostsHandler() {

}

GhostsHandler::~GhostsHandler() {

}

std::vector<Ghost *> *GhostsHandler::getGhosts() {
	return m_pGhosts;
}