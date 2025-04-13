#pragma once
#ifndef Game_h
#define Game_h

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <iostream>

#include "TextureManager.h"
#include "GameObject.h"


//Forward declarations
class GameObject;

//
template <typename T>
struct Vector2 {
	T x;
	T y;
};

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, SDL_WindowFlags flags);
	void clean();

	void loadFont();

	void loadEntities();
	void cleanEntities();

	void insertEntity(GameObject* entity);

	void handleEvents();
	void update();
	void render();

	bool running() { return isRunning; };
	Vector2<int> getWindowSize() { return windowSize; };

	SDL_Renderer* getRenderer() { return renderer; }

private:
	bool isRunning;
	Vector2<int> windowSize;
	SDL_Window* window;
	SDL_Renderer* renderer;

	TTF_Font* font{ nullptr };

	GameObject* Entities[64];
	int EntityCount = 0;

	int count = 0;
};

#endif //Game_h