#include "GameFont.h"

GameFont::GameFont(std::string fontType, int fontSize, SDL_Renderer *renderer) {
	m_pFont = TTF_OpenFont(fontType.c_str(), fontSize);
	m_pRenderer = renderer;
}

GameFont::~GameFont() {
	TTF_CloseFont(m_pFont);

	m_pFont = nullptr;
}

void GameFont::DrawText(std::string text, SDL_Color color, int x, int y) {
	SDL_Surface *textSurface = TTF_RenderText_Solid(m_pFont, text.c_str(), color);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_pRenderer, textSurface);

	int textWidth = 0;
	int textHeight = 0;

	SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
	SDL_Rect textSize = { x, y, textWidth, textHeight };

	SDL_RenderCopy(m_pRenderer, textTexture, nullptr, &textSize);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	textSurface = nullptr;
	textTexture = nullptr;
}