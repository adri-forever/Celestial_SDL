#include "ECS/SpriteComponent.h"

#include "TextureManager.h"

SpriteComponent::SpriteComponent(const char* path) {
	setTexture(path);
}

void SpriteComponent::setTexture(const char* path) {
	texture = TextureManager::loadTextureFile(path);
}