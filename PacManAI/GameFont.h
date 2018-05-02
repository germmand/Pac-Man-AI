#pragma once
#include <SDL_ttf.h>
#include <string>
#include <SDL.h>

class GameFont {
public:
	GameFont(std::string fontType, int fontSize, SDL_Renderer *renderer);
	~GameFont();

	void DrawText(std::string text, SDL_Color color, SDL_Rect *textSize);
private:
	TTF_Font *m_pFont;
	SDL_Renderer *m_pRenderer;
};