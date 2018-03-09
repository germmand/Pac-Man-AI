#include <iostream>
#include <SDL.h>
#include "GameScreen.h"

int main(int argc, char *argv[]) {
	// Se inicia SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL no se pudo inicializar. Error: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	// Se crea la pantalla del juego.
	GameScreen gameScreen;

	while (true) {
		if (SDL_PollEvent(gameScreen.getEvent())) {
			if (SDL_QUIT == gameScreen.getEvent()->type) {
				break;
			}
		}
	}
	// Se cierra SDL.
	SDL_Quit();
	return EXIT_SUCCESS;
}