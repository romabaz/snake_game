#include "GameWorld.h"

GameWorld::GameWorld()
{
	if (!initGraphicSystem()) {
		printf("\n[ERROR][GameWorld()] Failed to create GameWorld due to SDL failure");
	}
	else {
		sdlExists = true;
	}
}

GameWorld::~GameWorld()
{
	destroySDL();
}

void GameWorld::tick(const SDL_Event& sdlEvent)
{
	GameEvent ge = covertSDLEventToGameEvent(sdlEvent);
	for (GameObject* go : gameObjects) {
		go->tick(ge);
	}
}

void GameWorld::put(GameObject* gameObject)
{
	gameObject->init(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	gameObjects.push_back(gameObject);
}

void GameWorld::draw()
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);

	for (GameObject* go : gameObjects) {
		std::vector<DrawConstruct> dc = go->getDrawConstruct();
		if (go->getType() == SNAKEY) {
			texture->renderVector(dc);
		}
		else {
			texture->render(dc[0].type, { dc[0].x, dc[0].y });
		}
	}

	//Update screen 
	SDL_RenderPresent(gRenderer);
}

short GameWorld::initGraphicSystem()
{
	if (!initSDL()) {
		return 0;
	}
	if (!initSDLRenderer()) {
		SDL_Quit();
		return 0;
	}

	if (!initGameTexture()) {
		SDL_Quit();
		return 0;
	}

	return 1;
}

short GameWorld::initSDL() {
	printf("[TRACE][initSDL] Initializing SDL...");

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("\n[ERROR][initSDL] SDL couldn't initialize! SDL_ERROR: %s\n", SDL_GetError());
		return 0;
	}

	printf("success!\n");

	return 1;
}

short GameWorld::initSDLRenderer() {
	printf("[TRACE][initSDLRenderer] Constructing SDL renderer...");

	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		printf("\n[ERROR][initSDLRenderer] Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == nullptr) {
		printf("\n[ERROR][initSDLRenderer] Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(gWindow);
		gWindow = nullptr;
		return 0;
	}

	printf("success!\n");

	return 1;
}

short GameWorld::initGameTexture()
{
	texture = new GameTexture(gRenderer);
	if (!texture->load(defaultTexturePath)) {
		printf("[ERROR] Cannot load snake's head. Exiting...\n");
		delete texture;
		return 0;
	}
	return 1;
}

void GameWorld::destroySDL()
{
	printf("[TRACE][destroySDL] Destroying SDL...");
	//Destroy window 
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
	printf("success!\n");
}

GameEvent GameWorld::covertSDLEventToGameEvent(const SDL_Event sdlEvent)
{
	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		if (theLastOne == sdlEvent.key.keysym.sym) {
			break;
		}
		switch (sdlEvent.key.keysym.sym) {
		case SDLK_UP:
			theLastOne = SDLK_UP;
			return GE_UP;
		case SDLK_DOWN:
			theLastOne = SDLK_DOWN;
			return GE_DOWN;
		case SDLK_LEFT:
			theLastOne = SDLK_LEFT;
			return GE_LEFT;
		case SDLK_RIGHT:
			theLastOne = SDLK_RIGHT;
			return GE_GROW;
		case SDLK_SPACE:
			theLastOne = SDLK_SPACE;
			return GE_GROW;
		}
	}
	return GE_NONE;
}
