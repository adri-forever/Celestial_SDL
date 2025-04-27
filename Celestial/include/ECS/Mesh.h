#ifndef MESH_H
#define MESH_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ECS.h"
#include "TransformComponent.h"
#include "OpenGLRenderer.h"
#include "utils/glUtils.h"

class Mesh : public Component {
public:
	Mesh();
	Mesh(OpenGLRenderer* renderer, glm::vec3 icolor);
	~Mesh();

	glm::vec3 color;

	TransformComponent* transform;

	GLuint VAO=0, VBO=0;
	OpenGLRenderer* glRenderer;

	void init() override;
	void bind() const;
	void render();
};
#endif // MESH_H