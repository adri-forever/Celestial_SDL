#include "ECS/CircleComponent.h"

#include "Game.h"

CircleComponent::CircleComponent(double iradius, SDL_Color icolor) {
	radius = iradius;
	color = icolor;
}

void CircleComponent::render() {
	circleRGBA(Game::renderer, position->getX(), position->getY(), radius, color.r, color.g, color.b, color.a);
}