#include <iostream>
#include <SDL.h>
#include "GameScreen.h"

int main(int argc, char *argv[]) {
	// Se inicia SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL no se pudo inicializar. Error: " << SDL_GetError() << std::endl;
		SDL_Delay(3000);
		return EXIT_FAILURE;
	}

	// Se crea la pantalla del juego.
	GameScreen *game = new GameScreen();
	
	while (game->isRunning()) {
		while (SDL_PollEvent(game->getEvent()) != 0) {
			if (SDL_QUIT == game->getEvent()->type) {
				game->exitGame();
			} else if (SDL_KEYDOWN == game->getEvent()->type) {
				switch (game->getEvent()->key.keysym.sym) {
				case SDLK_UP:
					
					break;
				case SDLK_DOWN:
					
					break;
				case SDLK_RIGHT:
					
					break;
				case SDLK_LEFT:
					
					break;
				}
			}
		}
	}
	// Se libera la memoria.
	delete game;

	// Se cierra SDL.
	SDL_Quit();
	return EXIT_SUCCESS;
}