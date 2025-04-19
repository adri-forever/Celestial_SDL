#ifndef TextureManager_h
#define TextureManager_h

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class TextureManager {
public:
	static SDL_Texture* loadTextureFile(const char* fileName);

	static SDL_Texture* createText(const char* text, TTF_Font* font, SDL_Color color);
	
	static void renderTexture(SDL_Texture* tex, SDL_FRect src, SDL_FRect dest);
};

#endif //TextureManager_h