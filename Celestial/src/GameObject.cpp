#pragma once
#include "GameObject.h"

GameObject::GameObject(Game* g, SDL_Renderer* ren) {
	renderer = ren;
	game = g;
}

GameObject::~GameObject() {
	SDL_DestroyTexture(objTexture);
}

void GameObject::setTexture(SDL_Texture* texture) {
	objTexture = texture;
}

void GameObject::Update() {
	age++;

	//scale = .1 + 1.9*((age/50)%300)/300;

	//Randomly move 5 px left/right/up/down 
	int span = 5;
	xpos += std::rand() % (2*span+1) - span;
	ypos += std::rand() % (2*span+1) - span;

	//xpos += 5; //still move 5px right;

	//Contain it in the screen
	Vector2<int> windowSize;
	if (game != nullptr) {
		windowSize = game->getWindowSize();
	} else {
		windowSize = { 1280, 720 };
	}
	xpos %= windowSize.x;
	ypos %= windowSize.y;
	if (xpos < 0) {
		xpos += windowSize.x;
	}
	if (ypos < 0) {
		ypos += windowSize.y;
	}

	srcRect.h = objTexture->h;
	srcRect.w = objTexture->w;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;
}

void GameObject::Render() {
	SDL_RenderTexture(renderer, objTexture, &srcRect, &destRect);
}