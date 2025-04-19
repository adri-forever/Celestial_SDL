#include "Game.h"

//TextureManager textureManager;

SDL_Renderer* Game::renderer = nullptr; //this tells the compiler it needs to exist
EntityManager entityManager;
SDL_Event Game::event;

//Wacky init
auto& player(entityManager.addEntity());

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
		if (window) {
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, NULL);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;

		loadFont();

		player.addComponent<TransformComponent>(100, 100);
		//player.getComponent<PositionComponent>().setPos(0, 0);

		SDL_Color color{ 0xFF, 0xFF, 0xFF, 0xFF };

		/*player.addComponent<TextureComponent>();
		tex = TextureManager::createText("Lo", font, color);
		player.getComponent<TextureComponent>().setTexture(tex);*/
		player.addComponent<SpriteComponent>("assets/tyler1.png");
		player.addComponent<KeyboardController>();
		//player.addComponent<TextComponent>("Evil fucking skeleton!", font, color);
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
	switch (event.type) {
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;

		case SDL_EVENT_WINDOW_RESIZED:
			windowSize.set(event.window.data1, event.window.data2);
			std::cout << windowSize << std::endl;
			break;

		default:
			break;
	}
}

void Game::update() {
	entityManager.refresh();
	entityManager.update();
}

void Game::render() {
	SDL_RenderClear(renderer);
	//

	entityManager.render();

	//
	SDL_RenderPresent(renderer);
}

void Game::clean() {

	//cleanEntities();
	
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Travail termine !" << std::endl;
}