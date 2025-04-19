#include "ECS/TextComponent.h"

#include "TextureManager.h"

TextComponent::TextComponent(const char* text, TTF_Font* font, SDL_Color color) {
	setTexture(text, font, color);
}
void TextComponent::setTexture(const char* text, TTF_Font* font, SDL_Color color) {
	texture = TextureManager::createText(text, font, color);
}