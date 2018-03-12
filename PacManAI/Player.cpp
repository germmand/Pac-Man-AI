#include "Player.h"
#include "ScreenConfig.h"
#include <iostream>

Player::Player(SDL_Renderer *renderer, std::string spritePath) {
	SDL_Surface *surface = SDL_LoadBMP(spritePath.c_str());
	if (!surface) {
		std::cerr << spritePath << " couldn't be loaded." << std::endl;
	}

	m_pWindowRenderer = renderer;
	m_pPlayerTexture = SDL_CreateTextureFromSurface(m_pWindowRenderer, surface);

	SDL_QueryTexture(m_pPlayerTexture, nullptr, nullptr, &m_dSpriteWidth, &m_dSpriteHeight);
	m_dCurrentFrameX = m_dCurrentFrameY = 0;

	m_dFrameHeight = 4;
	m_dFrameWidth = 2;

	m_pDirection = new Movement();
	*m_pDirection = Movement::LEFT;

	m_pCurrentPosition = new SDL_Rect();
	*m_pCurrentPosition = {
		WIDTH / 2,  // x
		HEIGHT / 4, // y
		30,			// width
		30,			//height
	};

	m_pCurrentFrame = new SDL_Rect();
	*m_pCurrentFrame = {
		m_dCurrentFrameX, // x
		m_dCurrentFrameY, // y
		m_dSpriteWidth / m_dFrameWidth, // width
		m_dSpriteHeight / m_dFrameHeight, //height
	};

	m_dAnimationsPerSecond = 15;

	SDL_FreeSurface(surface);
}

Player::~Player() {
	delete m_pDirection;
	delete m_pCurrentFrame;
	delete m_pCurrentPosition;

	SDL_DestroyTexture(m_pPlayerTexture);
}

void Player::printPlayer() {
	SDL_RenderClear(m_pWindowRenderer);
	SDL_RenderCopy(m_pWindowRenderer, m_pPlayerTexture, m_pCurrentFrame, m_pCurrentPosition);
	SDL_RenderPresent(m_pWindowRenderer);
}

void Player::setDirection(Movement direction) {
	*m_pDirection = direction;
}

void Player::movePlayer() {
	int dSpeed = 5;

	switch (*m_pDirection) {
		case Movement::UP:
			if (m_pCurrentPosition->y > 0) {
				m_dCurrentFrameY = 2;
				m_pCurrentPosition->y -= dSpeed;
			}
			break;
		case Movement::DOWN:
			if (m_pCurrentPosition->y < HEIGHT - 30) {
				m_dCurrentFrameY = 3;
				m_pCurrentPosition->y += dSpeed;
			}
			break;
		case Movement::RIGHT:
			if (m_pCurrentPosition->x < WIDTH - 30) {
				m_dCurrentFrameY = 0;
				m_pCurrentPosition->x += dSpeed;
			}
			break;
		case Movement::LEFT:
			if (m_pCurrentPosition->x > 0) {
				m_dCurrentFrameY = 1;
				m_pCurrentPosition->x -= dSpeed;
			}
			break;
	}
}

void Player::updateAnimation(int *frameRate, int *currentFrame) {
	m_pCurrentFrame->y = m_dCurrentFrameY * m_pCurrentFrame->h;
	if (*frameRate / m_dAnimationsPerSecond == *currentFrame) {
		m_dCurrentFrameX = (m_dCurrentFrameX + 1) % m_dFrameWidth;
		m_pCurrentFrame->x = m_dCurrentFrameX * m_pCurrentFrame->w;
		*currentFrame = 0;
	}
}