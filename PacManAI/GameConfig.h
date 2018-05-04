#pragma once

/*
	WIDTH tiene que ser múltiplo de COLUMNS.
	HEIGHT tiene que ser múltiplo de ROWS.
	Para un mejor despliegue de los componentes.
*/

// Tamaño de la pantalla
#define WIDTH 700
#define HEIGHT 600

// Tamaño de la matriz.
#define COLUMNS 28
#define ROWS 30

// Cantidad de animaciones por defecto cada segundo
#define DEFAULT_ANIMATIONS_PER_SECOND 4

// Velocidad del juego.
#define GAME_DELAY_SPEED 45

// Pacman Node ID
#define PACMAN_ID 1200

// GHOSTS' ID
#define YELLOW_GHOST_ID 1201
#define RED_GHOST_ID 1202
#define PINK_GHOST_ID 1203
#define BLUE_GHOST_ID 1204