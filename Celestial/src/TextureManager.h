#pragma once
#ifndef TextureManager_h
#define TextureManager_h

#include "Game.h"
#include <string>

class TextureManager {
public:
	static SDL_Texture* LoadTextureFile(const char* fileName, SDL_Renderer* renderer);

	static SDL_Texture* CreateText(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* ren);
	
};

#endif //TextureManager_h