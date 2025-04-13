#pragma once
#ifndef TextureManager_h
#define TextureManager_h

#include "Game.h"
#include <string>

class TextureManager {
public:
	static SDL_Texture* LoadTextureFile(const char* fileName, SDL_Renderer* renderer);

	static SDL_Texture* CreateText(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* ren);
	
	static void Draw(SDL_Texture* tex, SDL_FRect src, SDL_FRect dest, SDL_Renderer* renderer);
};

#endif //TextureManager_h