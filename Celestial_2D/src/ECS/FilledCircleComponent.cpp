#include "ECS/FilledCircleComponent.h"

#include "Game.h"

FilledCircleComponent::FilledCircleComponent(double iradius, SDL_Color icolor) {
	radius = iradius;
	color = icolor;
}

void FilledCircleComponent::render() {
	filledCircleRGBA(Game::renderer, position->getX(), position->getY(), radius, color.r, color.g, color.b, color.a);
}