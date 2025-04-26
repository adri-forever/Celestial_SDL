#include "TextureManager.h"

#include "Game.h"
#include <string>

SDL_Texture* TextureManager::loadTextureFile(const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_DestroySurface(tempSurface);

	return tex;
}

SDL_Texture* TextureManager::createText(const char* text, TTF_Font* font, SDL_Color color) {
	SDL_Surface* tempSurface = TTF_RenderText_Blended(font, text, std::strlen(text), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_DestroySurface(tempSurface);

	return tex;
}

void TextureManager::renderTexture(SDL_Texture* tex, SDL_FRect src, SDL_FRect dest) {
	SDL_RenderTexture(Game::renderer, tex, &src, &dest);
}