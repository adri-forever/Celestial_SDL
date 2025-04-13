#include "Game.h"

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int width, int height, SDL_WindowFlags flags) {
	if (!SDL_Init(0)) {
		std::cout << "System initialization error: " << SDL_GetError() << std::endl;
		isRunning = false;
	} else {
		std::cout << "Systems initialized" << std::endl;
		windowSize = { width, height };
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

		loadEntities();
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

void Game::loadEntities() {
	GameObject* enemy = new GameObject(this, renderer);
	enemy->setTexture(TextureManager::LoadTextureFile("assets/evilfuckingskeleton.png", renderer));
	insertEntity(enemy);

	GameObject* player = new GameObject(this, renderer);
	player->setTexture(TextureManager::LoadTextureFile("assets/tyler1.png", renderer));
	insertEntity(player);

	SDL_Color txtcolor = { 0xFF, 0x80, 0xFF, 0x80 };
	GameObject* text = new GameObject(this, renderer);
	text->setTexture(TextureManager::CreateText("Evil!", font, txtcolor, renderer));
	insertEntity(text);
}

void Game::cleanEntities() {
	for (int i = 0; i < EntityCount; i++) {
		delete Entities[i];
	}
	EntityCount = 0;
	std::cout << "Entities cleaned" << std::endl;
}

void Game::insertEntity(GameObject* entity) {
	Entities[EntityCount] = entity;
	EntityCount++;
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;

		case SDL_EVENT_WINDOW_RESIZED:
			windowSize = { event.window.data1, event.window.data2 };
			std::cout << windowSize.x << " ; " << windowSize.y << std::endl;
			break;

		default:
			break;
	}
}

void Game::update() {
	for (int i = 0; i < EntityCount; i++) {
		Entities[i]->Update();
	}

	//Simulate lag (frame takes too much time to compute)
	/*if (500 < count && count < 600) {
		SDL_Delay(75);
	}*/
}

void Game::render() {
	SDL_RenderClear(renderer);
	//

	for (int i = 0; i < EntityCount; i++) {
		Entities[i]->Render();
	}

	//
	SDL_RenderPresent(renderer);
}

void Game::clean() {

	cleanEntities();
	
	TTF_CloseFont(font);
	TTF_Quit();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Travail termine !" << std::endl;
}