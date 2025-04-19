#ifndef KeyboardController_h
#define KeyboardController_h

#include "ECS.h"

class TransformComponent;

class KeyboardController : public Component {
private:
	TransformComponent* transform;
public:
	void init() override;

	void update() override;

};

#endif // !KeyboardController_h