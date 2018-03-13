#include <iostream>
#include <SDL.h>
#include "GameScreen.h"
#include "Character.h"
#include "Movement.h"

int main(int argc, char *argv[]) {
	// Se inicia SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL no se pudo inicializar. Error: " << SDL_GetError() << std::endl;
		SDL_Delay(3000);
		return EXIT_FAILURE;
	}

	// Se crea la pantalla del juego.
	GameScreen *game = new GameScreen();

	// Pacman
	Character *pacman = new Character("assets/pacman.bmp", game->getRenderer(), 2, 4);
	
	while (game->isRunning()) {
		while (SDL_PollEvent(game->getEvent()) != 0) {
			if (SDL_QUIT == game->getEvent()->type) {
				game->exitGame();
			} else if (SDL_KEYDOWN == game->getEvent()->type) {
				switch (game->getEvent()->key.keysym.sym) {
				case SDLK_UP:
					pacman->setDirection(Movement::UP);
					break;
				case SDLK_DOWN:
					pacman->setDirection(Movement::DOWN);
					break;
				case SDLK_RIGHT:
					pacman->setDirection(Movement::RIGHT);
					break;
				case SDLK_LEFT:
					pacman->setDirection(Movement::LEFT);
					break;
				}
			}
		}

		pacman->moveCharacter(game->getFPS());

		SDL_RenderClear(game->getRenderer());
		pacman->addToRenderer();
		SDL_RenderPresent(game->getRenderer());

		SDL_Delay(GAME_DELAY_SPEED);
	}
	// Se libera la memoria.
	delete pacman;
	delete game;

	// Se cierra SDL.
	SDL_Quit();
	return EXIT_SUCCESS;
}