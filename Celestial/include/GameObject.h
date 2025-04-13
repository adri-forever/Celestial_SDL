#pragma once
#ifndef GameObject_h
#define GameObject_h

#include "Game.h"
#include "TextureManager.h"
#include <iostream>

class Game;

class GameObject {
public:
	GameObject(Game* g, SDL_Renderer* ren);
	~GameObject();

	//Game* getGame() { return game; };

	void setTexture(SDL_Texture* texture);

	void Update();
	void Render();

private:
	Game* game = nullptr;

	int xpos = 0;
	int ypos = 0;
	int scale = 1;
	int age = 0;

	SDL_Texture* objTexture = nullptr;
	SDL_FRect srcRect, destRect;
	SDL_Renderer* renderer = nullptr;
};

#endif //GameObject_h