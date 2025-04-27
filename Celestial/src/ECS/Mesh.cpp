#include "ECS/Mesh.h"

// Simple triangle data
float vertices[] = {
    // Positions
	0.f, 0.f, 0.f,
	1.f, 0.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 0.f, 1.f,
	0.f, 0.f, 0.f
};

Mesh::Mesh() {}

Mesh::Mesh(OpenGLRenderer* renderer, glm::vec3 icolor) {
	glRenderer = renderer;
	color = icolor;
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Mesh::init() {
	transform = &entity->getComponent<TransformComponent>();
	// Generate and bind the Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//std::cout << "Binding VAO " << VAO << std::endl;

	// Generate and bind the Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//std::cout << "Binding VBO " << VBO << std::endl;

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::bind() const {
	glBindVertexArray(VAO);
}

void Mesh::render() {
	std::cout << "Drawing entity at " << transform->position << std::endl;
	//Set position
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((float)transform->position.x, (float)transform->position.y, (float)transform->position.z));
	glRenderer->setMat4("model", &model[0][0]);
	
	//Set color
	glUniform3f(glGetUniformLocation(glRenderer->shaderProgram, "color"), color.r, color.g, color.b);

	bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
}