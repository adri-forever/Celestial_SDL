#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
	
	SDL_Window* window = nullptr;
	SDL_Surface* windowSurface = nullptr;
	SDL_Surface* imageSurface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Video initialization error: " << SDL_GetError() << std::endl;
	} else {
		window = SDL_CreateWindow("Celestial - ARI", 1280, 720, SDL_WINDOW_RESIZABLE);
		if (window == NULL) {
			std::cout << "Window creation error: " << SDL_GetError() << std::endl;
		} else {
			windowSurface = SDL_GetWindowSurface(window);
			imageSurface = SDL_LoadBMP("earf.bmp");

			if (imageSurface == NULL) {
				std::cout << "Image loading error: " << SDL_GetError() << std::endl;
			} else {
				SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
				SDL_UpdateWindowSurface(window);
				SDL_Delay(10000);
			}
		}
	}

	SDL_DestroySurface(imageSurface);
	imageSurface = nullptr;

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}