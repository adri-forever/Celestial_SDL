#include "ECS/TextureComponent.h"

#include "TextureManager.h"

void TextureComponent::render() {
	TextureManager::renderTexture(texture, srcRect, destRect);
}