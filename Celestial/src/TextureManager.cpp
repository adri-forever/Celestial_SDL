#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTextureFile(const char* texture, SDL_Renderer* ren) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_DestroySurface(tempSurface);

	return tex;
}

SDL_Texture* TextureManager::CreateText(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* ren) {
	SDL_Surface* tempSurface = TTF_RenderText_Blended(font, text, std::strlen(text), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_DestroySurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_FRect src, SDL_FRect dest, SDL_Renderer* renderer) {
	SDL_RenderTexture(renderer, tex, &src, &dest);
}