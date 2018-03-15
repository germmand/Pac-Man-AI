#pragma once


// PACMAN y GHOST no se incluirán en AssetType ya que se manejarán de manera independiente (fuera del mapa).
// Para que sea más fácil la manipulación de cada uno a la hora de implementarles la inteligencia artificial.

enum AssetType : int {
	NONE		= 0,
	WALL		= 1,
	FOOD		= 2,
	BOOSTFOOD	= 3,
	FRUIT		= 4
};