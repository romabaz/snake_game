#include "include/GameWorld.h"

GameWorld::GameWorld()
{
	if (!initGraphicSystem()) {
		printf("\n[ERROR][GameWorld()] Failed to create GameWorld due to SDL failure");
	}
	else {
		sdlExists = true;
		srand(time(nullptr));
	}
}

GameWorld::~GameWorld()
{
	destroySDL();
	for (GameObject* go : gameObjects) {
		if (go != nullptr) {
			delete go;
		}
	}
}

/*
1. Convert SDL_Event to GameEvent
2. Apply game event to each game object
*/
void GameWorld::propagate(const SDL_Event& sdlEvent)
{
	GameEvent ge = covertSDLEventToGameEvent(sdlEvent);
	for (GameObject* go : gameObjects) {
		go->applyGameEvent(ge);
	}
}

/*
1. detect collisions
2. move
*/
void GameWorld::tick()
{
	CollisionZone headCollisionZone = snakeyObject->getCollisionZone();
	for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++) {
		GameObject* go = (*it);
		if (go->getType() != SNAKEY) {
			if (intersect(headCollisionZone, go->getCollisionZone())) {
				GameObjectType goType = go->getType();
				if (goType == FOOD_APPLE || goType == FOOD_CARROT || goType == FOOD_LEAF || goType == FOOD_POTATO) {
					/*
					1. delete food
					2. grow snake
					3. generate new food
					4. change background colour
					*/
					it = gameObjects.erase(it);
					delete go;
					snakeyObject->applyGameEvent(GE_GROW);
					put(new Food(), true);
					gRColour = rand() % 255;
					gGColour = rand() % 255;
					gBColour = rand() % 255;
				}
				break;
			}
		}
		else {
			go->move();
		}
	}
}

void GameWorld::put(GameObject* gameObject, bool random)
{
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 2;
	if (random) {
		x = rand() % (SCREEN_WIDTH - 50);
		y = rand() % (SCREEN_HEIGHT - 50);
		
	}
	if (gameObject->getType() == SNAKEY) {
		snakeyObject = gameObject;
	}
	gameObject->init(x, y);
	gameObjects.push_back(gameObject);
}

void GameWorld::draw()
{
	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, gRColour, gGColour, gBColour, 0xFF);
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

bool GameWorld::intersect(const CollisionZone & a, const CollisionZone & b)
{
	int leftA, leftB; 
	int rightA, rightB; 
	int topA, topB;
	int bottomA, bottomB; 

	leftA = a.topLeft.x;
	rightA = a.topLeft.x + a.width; 
	topA = a.topLeft.y;
	bottomA = a.topLeft.y + a.height; 

	leftB = b.topLeft.x;
	rightB = b.topLeft.x + b.width;
	topB = b.topLeft.y;
	bottomB = b.topLeft.y + b.height;
	if (leftA >= rightB) {
		return false;
	}
	if (rightA <= leftB) {
		return false;
	}
	if (topA >= bottomB) {
		return false;
	}
	if (bottomA <= topB) {
		return false;
	}
	return true;
}

GameEvent GameWorld::covertSDLEventToGameEvent(const SDL_Event sdlEvent)
{
	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		switch (sdlEvent.key.keysym.sym) {
		case SDLK_UP:
			return GE_UP;
		case SDLK_DOWN:
			return GE_DOWN;
		case SDLK_LEFT:
			return GE_LEFT;
		case SDLK_RIGHT:
			return GE_RIGHT;
		case SDLK_SPACE:
			return GE_GROW;
		}
	}
	return GE_NONE;
}
