#pragma once


// PACMAN y GHOST no se incluir�n en AssetType ya que se manejar�n de manera independiente (fuera del mapa).
// Para que sea m�s f�cil la manipulaci�n de cada uno a la hora de implementarles la inteligencia artificial.

enum AssetType : int {
	NONE		= 0,
	WALL		= 1,
	FOOD		= 2,
	BOOSTFOOD	= 3,
	FRUIT		= 4
};