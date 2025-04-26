#ifndef CircleComponent_h
#define CircleComponent_h

#include <SDL3/SDL.h>

#include "ECS.h"
#include "TransformComponent.h"

class CircleComponent : public Component {
protected:
	SDL_Color color;
	double radius;

	TransformComponent* position;

public:
	CircleComponent() = default;
	CircleComponent(double iradius, SDL_Color icolor);
	~CircleComponent() = default;

	void init() override { position = &entity->getComponent<TransformComponent>(); }

	void render() override;
};

#endif // !CircleComponent_h
