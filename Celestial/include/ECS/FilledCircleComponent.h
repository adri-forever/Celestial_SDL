#ifndef FilledCircleComponent_h
#define FilledCircleComponent_h

#include <SDL3/SDL.h>

#include "CircleComponent.h"

class FilledCircleComponent : public CircleComponent {
public:
	FilledCircleComponent() = default;
	FilledCircleComponent(double iradius, SDL_Color icolor);

	void render() override;
};

#endif // !FilledCircleComponent_h
