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
	GameScreen *gameScreen = new GameScreen();

	GameAsset asset = GameAsset("assets/food.bmp");
	
	while (gameScreen->isRunning()) {
		if (SDL_PollEvent(gameScreen->getEvent())) {
			if (SDL_QUIT == gameScreen->getEvent()->type) {
				gameScreen->exitGame();
			}
		}

		gameScreen->paintAsset(&asset);
		gameScreen->updateScreen();
	}
	// Se libera la memoria.
	delete gameScreen;

	// Se cierra SDL.
	SDL_Quit();
	return EXIT_SUCCESS;
}