#ifndef Game_h
#define Game_h

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_gfxPrimitives.h>

#include <iostream>

#include "TextureManager.h"
#include "ECS/Components.h"

#include "utils/Vector2.h"

class Game {
private:
	bool isRunning = false;
	Vector2<int> windowSize;
	SDL_Window* window;

	TTF_Font* font{ nullptr };

public:
	Game();
	~Game();

	static SDL_Renderer* renderer;
	static SDL_Event event;

	void init(const char* title, int width, int height, SDL_WindowFlags flags);
	void clean();

	void loadFont();

	void handleEvents();
	void update(int framelength);
	void render();

	bool running() const { return isRunning; };
	Vector2<int> getWindowSize() const { return windowSize; };
	
	void toggleCursor();
	void toggleCursor(bool state);
	//also lock mouse in the window when hidden 
};

#endif //Game_h