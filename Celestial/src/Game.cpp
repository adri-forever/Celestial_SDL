#include "Game.h"

SDL_Renderer* Game::renderer = nullptr; //this tells the compiler it needs to exist
EntityManager entityManager;
SDL_Event Game::event;

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
// => tester la superposition en spawnant différents acteurs superposés

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
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;

		loadFont();

		//player.addComponent<TransformComponent>(100, 100);

		SDL_Color color{ 0x00, 0xFF, 0xFF, 0xFF };

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

		case SDL_EVENT_KEY_DOWN:
			switch (event.key.key) {
			case SDLK_ESCAPE:
				isRunning = false;
				break;
			case SDLK_TAB:
				toggleCursor();
			default:
				break;
			}
		default:
			break;
	}
}

void Game::update(int framelength) {
	entityManager.refresh();
	entityManager.update();
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderClear(renderer);
	//

	// Render all the layers in the right order based on groups
	for (auto& t : groupOrder) {
		for (auto& e : entityManager.getGroup(t)) {
			e->render();
		}
	}
	//Groupless entities will not be rendered

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

void Game::toggleCursor() {
	toggleCursor(!SDL_CursorVisible());
}

void Game::toggleCursor(bool state) {
	if (state) {
		SDL_ShowCursor();
	} else {
		SDL_HideCursor();
	}
}