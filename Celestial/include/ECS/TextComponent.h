#ifndef TextComponent_h
#define TextComponent_h

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "TextureComponent.h"

class TextComponent : public TextureComponent {
public:
	TextComponent() = default;
	TextComponent(const char* text, TTF_Font* font, SDL_Color color);

	void setTexture(const char* text, TTF_Font* font, SDL_Color color);
};

#endif // !TextComponent_h
