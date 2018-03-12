#pragma once

#include <SDL.h>
#include <string>

enum Movement : int {
	RIGHT = 1,
	LEFT  = 2,
	UP    = 3,
	DOWN  = 4
};

class Player {
private:
	SDL_Renderer *m_pWindowRenderer;
	SDL_Texture *m_pPlayerTexture;
	int m_dSpriteWidth, m_dSpriteHeight;
	int m_dCurrentFrameX, m_dCurrentFrameY;
	int m_dFrameWidth, m_dFrameHeight;
	int m_dAnimationsPerSecond;
	Movement *m_pDirection;
	SDL_Rect *m_pCurrentFrame, *m_pCurrentPosition;

public:
	Player(SDL_Renderer *renderer, std::string spritePath);
	~Player();

	void printPlayer();
	void setDirection(Movement direction);
	void movePlayer();
	void updateAnimation(int *frameRate, int *currentFrame);
};