#include "OpenGLRenderer.h"

#include "utils/glUtils.h"

OpenGLRenderer::OpenGLRenderer() {};

OpenGLRenderer::~OpenGLRenderer() {
	SDL_GL_DestroyContext(glContext);
}

void OpenGLRenderer::init(SDL_GLContext context) {
	glContext = context;

	glClearColor(.2f, .2f, .2f, 1.0f);

	//Build shader program
	const char* vertexShaderSource = R"(
			#version 460 core
			layout (location = 0) in vec3 aPos;
			
			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

			void main() {
				gl_Position = projection * view * model * vec4(aPos, 1.0);
			}
		)";
	const char* fragmentShaderSource = R"(
			#version 460 core

			out vec4 FragColor;

			uniform vec3 color;

			void main() {
				FragColor = vec4(color, 1.0);
			}
		)";

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkShaderCompile(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderCompile(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkProgramLink(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void OpenGLRenderer::use() const {
	glUseProgram(shaderProgram);
}

void OpenGLRenderer::render() {

}

void OpenGLRenderer::setMat4(const std::string& name, const float* mat) const {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, mat);
}