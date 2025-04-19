#ifndef Game_h
#define Game_h

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <iostream>

#include "utils/Vector2.h"
#include "TextureManager.h"
#include "ECS/Components.h"

class Game {
private:
	bool isRunning;
	Vector2<int> windowSize;
	SDL_Window* window;

	TTF_Font* font{ nullptr };

public:
	Game();
	~Game();

	void init(const char* title, int width, int height, SDL_WindowFlags flags);
	void clean();

	void loadFont();

	void handleEvents();
	void update();
	void render();

	bool running() const { return isRunning; };
	Vector2<int> getWindowSize() const { return windowSize; };

	static SDL_Renderer* renderer;
	static SDL_Event event;
};

#endif //Game_h