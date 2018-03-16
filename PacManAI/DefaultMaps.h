#pragma once

#include "GameConfig.h"

/*
X -> Wall.
C -> Pacman.
*/
char map_one[ROWS][COLUMNS + 1] = {
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	"X            XXX          XX",
	"X XXX XXXXX XXXXX XXXXX X XX",
	"X XXX XXXXX XXXXX XXXXX X XX",
	"X                          X",
	"X XXX XX XXXXXXXXXXX XX XX X",
	"X     XX     XXX     XX XX X",
	"X XXX XXXXXX XXX XXXXXX XX X",
	"X XXX XX             XX XX X",
	"      XX XXXXXXXXXXX XX     ",
	"X XXX XX XXXXXXXXXXX XX XX X",
	"X XXX XX             XX XX X",
	"X XXX XXXXXX XXX XXXXXX XX X",
	"X     XX     XXX     XX    X",
	"X XXX XX XXXXXXXXXXX XX XX X",
	"X XXX                   XX X",
	"X XXX XXXX XXXXXXXX XXX XX X",
	"X XXX XXXX          XXX XX X",
	"X          XXXXXXXX        X",
	"X XXX XX XXXXXXXXXXX XX XX X",
	"X XXX XX XXXXXXXXXXX XX XX X",
	"X XXX XX             XX XX X",
	"X XXX XXXXXX XXX XXXXXX XX X",
	"      XX     XXX     XX     ",
	"X XXX XX XXXXXXXXXXX XX XX X",
	"X XXX         C         XX X",
	"X XXX XXXX XXXXXXXX XXX XX X",
	"X XXX XXXX          XXX XX X",
	"X          XXXXXXXX        X",
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};