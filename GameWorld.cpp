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

void GameWorld::drawFunction(const GameObject* gameObject)
{
	if (gameObject->getType() == SNAKEY) {
		//process each quantum
	}
	else {
		texture->render(gameObject->getType(), { gameObject->getXPosition(), gameObject->getYPosition() });
	}
}

void GameWorld::put(const GameObject & gameObject)
{
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