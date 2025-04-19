#ifndef TextureComponent_h
#define TextureComponent_h

#include <SDL3/SDL.h>

#include "ECS.h"
#include "TransformComponent.h"

class TextureComponent : public Component {
protected:
	TransformComponent* position;
	SDL_Texture* texture;
	SDL_FRect srcRect, destRect;

public:
	TextureComponent() = default;

	void init() override {
		position = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		if (texture != nullptr) {
			srcRect.w = texture->w;
			srcRect.h = texture->h;
		}
		destRect.h = srcRect.h;
		destRect.w = srcRect.w;
	}

	void update() override {
		destRect.x = (int)position->getX();
		destRect.y = (int)position->getY();
	}

	void render() override;
	
	void setTexture(SDL_Texture* tex) { //does not work for some reason
		texture = tex;
	}
};

#endif // !TextureComponent_h
