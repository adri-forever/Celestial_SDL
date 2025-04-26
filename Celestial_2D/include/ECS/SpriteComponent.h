#ifndef SpriteComponent_h
#define SpriteComponent_h

#include <SDL3/SDL.h>

#include "TextureComponent.h"

class SpriteComponent : public TextureComponent {
public:
	SpriteComponent(const char* path);

	void setTexture(const char* path);
};

#endif // !SpriteComponent_h
