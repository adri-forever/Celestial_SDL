#include "Game.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

EntityManager Game::entityManager;
SDL_Event Game::event;
OpenGLRenderer Game::glRenderer;

//Wacky init
//auto& player(entityManager.addEntity());

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
	groupParticles,
	groupUI
};

constexpr groupLabels groupOrder[] = {
	groupLabels::groupMap,
	groupLabels::groupPlayers,
	groupLabels::groupEnemies,
	groupLabels::groupColliders,
	groupLabels::groupParticles,
	groupLabels::groupUI
};

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int width, int height, SDL_WindowFlags flags) {
	if (!SDL_Init(0)) {
		std::cout << "System initialization error: " << SDL_GetError() << std::endl;
		isRunning = false;
	} else {
		std::cout << "Systems initialized" << std::endl;
		
		windowSize = Vector2<int>(width, height);
		window = SDL_CreateWindow(title, width, height, flags);
		//SDL_WindowFlags windowFlags = SDL_GetWindowFlags(window);
		
		if (window) {
			std::cout << "Window created" << std::endl;
			//std::cout << "Requested flags: " << windowFlags << std::endl;
		}

		/*renderer = SDL_CreateRenderer(window, NULL);
		if (renderer) {
			std::cout << "Renderer created" << std::endl;
		}*/
		 
		if ((flags & SDL_WINDOW_OPENGL) != 0) {
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

			SDL_GLContext glContext = SDL_GL_CreateContext(window);
			if (glContext) {
				std::cout << "OpenGL context created" << std::endl;
			} else {
				std::cout << "OpenGL context creation error: " << SDL_GetError() << std::endl;
			}
			SDL_GL_SetSwapInterval(1); //VSync

			SDL_GL_MakeCurrent(window, glContext);
			
			if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
				std::cout << "GLAD loading error: " << SDL_GetError() << std::endl;
			}

			glRenderer.init(glContext);
		} else {
			std::cout << "OpenGL not requested" << std::endl;
		}

		isRunning = true;

		//std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

		//loadFont();

		//player.addComponent<TransformComponent>(100, 100);

		//SDL_Color color{ 0x00, 0xFF, 0xFF, 0xFF };

		//Texturing test
		/*player.addComponent<TextureComponent>();
		tex = TextureManager::createText("Lo", font, color);
		player.getComponent<TextureComponent>().setTexture(tex);*/
		//player.addComponent<SpriteComponent>("assets/tyler1.png");
		//player.addComponent<CircleComponent>(50, color);
		//player.addComponent<KeyboardController>();
		//player.addGroup(groupPlayers);
		//player.addComponent<TextComponent>("Evil fucking skeleton!", font, color);
		
		//Layering test
		/*int i2;
		for (int i=0; i<SDL_arraysize(groupOrder); i++) {
			i2 = SDL_arraysize(groupOrder) - i - 1;
			std::cout << "Adding entity to group " << i2 << std::endl;
			auto& e(entityManager.addEntity());
			e.addGroup(groupOrder[i2]);
			e.addComponent<TransformComponent>(10 * i, 10 * i);
			e.addComponent<SpriteComponent>("assets/tyler1.png");
		}*/

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glm::vec3 color1(1.f, 0.f, 0.f);
		glm::vec3 color2(0.f, 1.f, 1.f);
		auto& e1(entityManager.addEntity());
		e1.addComponent<TransformComponent>(-.5, 0., 0.);
		e1.addComponent<Mesh>(&glRenderer, color1);
		std::cout << e1.getComponent<TransformComponent>().position << std::endl;

		auto& e2(entityManager.addEntity());
		e2.addComponent<TransformComponent>(.5, 0., 0.);
		e2.addComponent<Mesh>(&glRenderer, color2);

		//projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
		projection = glm::perspective(glm::radians(90.f), (float)width / (float)height, 0.1f, 100.f);
	}
}

void Game::loadFont() {
	TTF_Init();

    std::string fontPath = "assets/font/segoeui.ttf";
	font = TTF_OpenFont(fontPath.c_str(), 72);
	if (font == nullptr) {
		std::cout << "Could not load " << fontPath << " SDL_ttf Error : " << SDL_GetError() << std::endl;
	} else {
		std::cout << "Font " << fontPath << " loaded " << std::endl;
	}
}

void Game::handleEvents() {
	SDL_PollEvent(&event);
	//std::cout << "Handling event of type " << event.type << std::endl;
	switch (event.type) {
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;

		case SDL_EVENT_WINDOW_RESIZED:
			windowSize.set(event.window.data1, event.window.data2);
			glViewport(0, 0, event.window.data1, event.window.data2); //Synchronize OpenGL viewport size
			std::cout << windowSize << std::endl;
			break;

		case SDL_EVENT_KEY_DOWN:
			switch (event.key.key) {
			case SDLK_ESCAPE:
				isRunning = false;
				break;
			case SDLK_TAB:
				toggleCursor();
			default:
				break;
			}/*
		case SDL_EVENT_MOUSE_MOTION:
			std::cout << "Mouse moved to " << event.motion.x << ", " << event.motion.y << std::endl;
			if (!SDL_CursorVisible()
				&& (std::abs(event.motion.x - windowSize.getX()) > 64
					|| std::abs(event.motion.y - windowSize.getY()) > 64)
				) {
				SDL_WarpMouseInWindow(window, windowSize.getX() / 2, windowSize.getY() / 2 );
				std::cout << "Mouse force moved" << std::endl;
			}*/
		default:
			break;
	}
}

void Game::update(int framelength) {
	entityManager.refresh();
	entityManager.update();

	age++;
}

void Game::render() {
	//Set empty color & clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glRenderer.use();
	glRenderer.setMat4("projection", &projection[0][0]);


	glm::vec3 cameraPos = glm::rotateY(glm::vec3(1.5f, 1.5f, 0.f), glm::radians((float)age));
	glm::vec3 cameraTarget(0.f, 0.f, 0.f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up(0.f, 1.f, 0.f);

	glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, up);
	//glm::mat4 view = glm::mat4(1.f);
	glRenderer.setMat4("view", &view[0][0]);
	//std::cout << "View matrix: " << glm::to_string(view) << std::endl;

	std::cout << "Camera Position: " << cameraPos << std::endl;
	std::cout << "Camera Target: " << cameraTarget << std::endl;

	entityManager.render();

	SDL_GL_SwapWindow(window);
}

void Game::clean() {
	/*glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &VAO);*/
	
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_DestroyWindow(window);
	//SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Travail termine !" << std::endl;
}

void Game::toggleCursor() {
	toggleCursor(!SDL_CursorVisible());
}

void Game::toggleCursor(bool state) {
	if (state) {
		SDL_WarpMouseInWindow(window, windowSize.getX()/2, windowSize.getY()/2);
		SDL_ShowCursor();
		SDL_SetWindowMouseGrab(window, false);
	} else {
		SDL_HideCursor();
		SDL_SetWindowMouseGrab(window, true);
	}
}