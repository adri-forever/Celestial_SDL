#include <iostream>

#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	const int framerate = 120; // FPS
	const int framelength = 1000 / framerate; // ms

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("Celestial", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update(framelength);
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (framelength > frameTime) {
			SDL_Delay(framelength - frameTime);
		}
	}

	game->clean();

	delete game;
	return 0;
}