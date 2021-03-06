#include <iostream>
#include <SDL.h>
#include "GameScreen.h"
#include "Character.h"
#include "Movement.h"
#include "GameMap.h"
#include "GhostsHandler.h"
#include <SDL_ttf.h>
#include "GameFont.h"
#include "ANodeHandler.h"
#include "ANode.h"
#include "NodeType.h"
#include "Utils.h"

int main(int argc, char *argv[]) {
	// Se inicia SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL no se pudo inicializar. Error: " << SDL_GetError() << std::endl;
		SDL_Delay(3000);
		return EXIT_FAILURE;
	}

	// Se inicia la librer�a para las fuentes.
	TTF_Init();

	// Variable para controlar si la ventana deber�a cerrarse o no.
	bool bShouldCloseWindow = false;
	
	while (!bShouldCloseWindow) {
		// Se crea la pantalla del juego.
		GameScreen *game = new GameScreen();

		// Pacman
		Character *pacman = new Character(new ANode(NodeType::PACMAN_NODE, 0, 0, PACMAN_ID), game, AssetType::PACMAN, "assets/pacman.bmp", game->getRenderer(), 2, 4);

		// Se crea el manipulador de fantasmas,
		GhostsHandler *ghostsHandler = new GhostsHandler();

		// Se crea el manipulador de nodos.
		ANodeHandler *ANodesHandler = new ANodeHandler();

		// Map
		GameMap *map = new GameMap(game->getRenderer());
		map->loadMap(pacman, ghostsHandler, game, ANodesHandler);

		while (game->getRemainingLives() > 0 && !game->getGameWon()) {
			while (game->isRunning()) {
				while (SDL_PollEvent(game->getEvent()) != 0) {
					if (SDL_QUIT == game->getEvent()->type) {
						game->exitGame();
						bShouldCloseWindow = true;
					}
					else if (SDL_KEYDOWN == game->getEvent()->type) {
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

			if (!game->getGameWon()) {
				game->decreaseLives();

				if (game->getRemainingLives() > 0 && !bShouldCloseWindow) {
					std::cout << "----------" << std::endl;
					std::cout << "Cantidad total de puntos: " << pacman->getTotalPoints() << std::endl;
					Utils::WaitForKey("Tienes " + std::to_string(game->getRemainingLives()) + " vidas restantes, presiona 'r' para continuar...", nullptr);
					pacman->RestoreToSpawnPosition();
					ghostsHandler->restoreGhostsToSpawnPos();
					game->setIsRunning(true);
				}
			}
			else {
				std::cout << "Has ganado el juego!" << std::endl;
			}
		}

		std::cout << "----------" << std::endl;
		std::cout << "Cantidad total de puntos: " << pacman->getTotalPoints() << std::endl;

		/*
		GameFont *gameOverText = new GameFont("arial.ttf", 25, game->getRenderer());
		gameOverText->DrawText("Game Over!", { 255, 255, 255 }, 50, 50);
		delete gameOverText;
		gameOverText = nullptr;
		*/

		// Se libera la memoria.
		delete map;
		delete pacman;
		delete ghostsHandler;
		delete ANodesHandler;
		delete game;

		map				= nullptr;
		pacman			= nullptr;
		ghostsHandler	= nullptr;
		ANodesHandler	= nullptr;
		game			= nullptr;

		Utils::WaitForKey("El juego ha terminado! Presiona 'R' para reiniciar o cualquier otra tecla para salir...", &bShouldCloseWindow);
	}

	// Se cierra SDL.
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}