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

	// Esto es para la prueba con el renderer...
	SDL_Rect *foodCoord = new SDL_Rect();
	foodCoord->x = foodCoord->y = 0;
	foodCoord->w = foodCoord->h = 9;
	GameAsset *food = new GameAsset("assets/food.bmp", game->getRenderer(), foodCoord);
	
	while (game->isRunning()) {
		while (SDL_PollEvent(game->getEvent()) != 0) {
			if (SDL_QUIT == game->getEvent()->type) {
				game->exitGame();
			}
		}

		food->printAsset();
	}
	// Se libera la memoria.
	delete food;
	delete game;

	// Se cierra SDL.
	SDL_Quit();
	return EXIT_SUCCESS;
}