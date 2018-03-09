#include <iostream>
#include "SDL.h"

int main(int argc, char *argv[]) {
	// Se inicia SDL.
	SDL_Init(SDL_INIT_EVERYTHING);

	// Se cierra SDL.
	SDL_Quit();
	return 0;
}