#include "Utils.h"
#include <iostream>
#include <conio.h> // Deprecado. Pero para uso de _kbhit y _getch para determinar si cerrar la ventana al finalizar el juego.


void Utils::WaitForKey(std::string message, bool *closeWindow) {
	std::cout << message << std::endl;

	bool breakLoop = false;
	while (true) {
		if (_kbhit()) {
			switch (_getch()) {
			case 'r' || 'R':
				breakLoop = true;
				if(closeWindow != nullptr) *closeWindow = false;
				break;
			default:
				breakLoop = true;
				if (closeWindow != nullptr) *closeWindow = false;
			}
		}

		if (breakLoop) break;
	}
}