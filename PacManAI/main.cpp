#include <iostream>
#include <SDL.h>
#include "GameScreen.h"
#include "Character.h"
#include "Movement.h"
#include "GameMap.h"
#include "GhostsHandler.h"

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
	Character *pacman = new Character(AssetType::PACMAN, "assets/pacman.bmp", game->getRenderer(), 2, 4);

	// Se crea el manipulador de fantasmas,
	GhostsHandler *ghostsHandler = new GhostsHandler();

	// Map
	GameMap *map = new GameMap(game->getRenderer());
	map->loadMap(pacman, ghostsHandler, game);
	
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
		ghostsHandler->moveGhosts(game->getFPS());

		SDL_RenderClear(game->getRenderer());
		map->renderMap();
		ghostsHandler->renderGhosts();
		pacman->addToRenderer();
		SDL_RenderPresent(game->getRenderer());

		SDL_Delay(GAME_DELAY_SPEED);
	}
	// Se libera la memoria.
	delete map;
	delete pacman;
	delete ghostsHandler;
	delete game;

	map				= nullptr;
	pacman			= nullptr;
	ghostsHandler	= nullptr;
	game			= nullptr;

	// Se cierra SDL.
	SDL_Quit();
	return EXIT_SUCCESS;
}