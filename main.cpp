#include<stdio.h>
#include<math.h>
#include"Snake.h"

#define PI 3.14159265359
//SDL rendering entities
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


//Basic coordinates
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 800;

const int ZERO_X = 100;
const int ZERO_Y = 700;


//Snake global
Snake* gSnake;

short initSDL() {
	printf("[TRACE][initSDL] Initializing SDL...");

	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("\n[ERROR][initSDL] SDL couldn't initialize! SDL_ERROR: %s\n", SDL_GetError());
		return 0;
	}

	printf("success!\n");

	return 1;
}


short initSDLRenderer() {
	printf("[TRACE][initSDLRenderer] Constructing SDL renderer...");

	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL){
		printf("\n[ERROR][initSDLRenderer] Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL) {
		printf("\n[ERROR][initSDLRenderer] Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
		return 0;
	}

	printf("success!\n");

	return 1;
}

void destroySDL()
{
	printf("[TRACE][destroySDL] Destroying SDL...");
	//Destroy window 
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	//Quit SDL subsystems
	SDL_Quit();
	printf("success!\n");
}

short initGraphics(){
	if (!initSDL()) {
		return 0;
	}
	if (!initSDLRenderer()) {
		SDL_Quit();
		return 0;
	}
	return 1;
}

short mousePoints(int mouseX, int mouseY){
	return 1;
}

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
	int x, y;
	double val = PI / 180;
	for (int i = 0; i < 360; i+=3) {
		double radVal = i * val;
		x = radius*cos(radVal) + centerX;
		y = radius*sin(radVal) + centerY;
		SDL_RenderDrawPoint(renderer, x, y);
	}
	return;
}

int main(int argc, char* args[]){
	
	printf("[TRACE] Snake has started\n");
	if (!initGraphics()){
		printf("[TRACE] Exiting...");
		return 0;
	}

	GameTexture* headTexture = new GameTexture(gRenderer);
	if (!headTexture->load("head.bmp")) {
		printf("[ERROR] Cannot load snake's head. Exiting...\n");
		destroySDL();
		delete headTexture;
		return 0;
	}

	gSnake = new Snake(headTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	short currentSpeed = gSnake->getSpeed();
	short quit = 0;
	SDL_Event e;
	int currMouseX = 0, currMouseY = 0;
	
	while (!quit) {
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0){
			switch (e.type) {
			case SDL_QUIT:
				quit++;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit++;
					break;
				case SDLK_w:
					gSnake->setSpeed(++currentSpeed);
					break;
				case SDLK_s:
					if (currentSpeed > 0) {
						gSnake->setSpeed(--currentSpeed);
					}
					break;
				case SDLK_UP:
					gSnake->setDirection(UP);
					break;
				case SDLK_DOWN:
					gSnake->setDirection(DOWN);
					break;
				case SDLK_LEFT:
					gSnake->setDirection(LEFT);
					break;
				case SDLK_RIGHT:
					gSnake->setDirection(RIGHT);
					break;
				case SDLK_SPACE:
					gSnake->addBodyChain(headTexture);
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&currMouseX, &currMouseY);
				break;
			}
		}
		//Clear screen '
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		//Track mouse
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
		drawCircle(gRenderer, currMouseX, currMouseY, 7);

		//render snake
		gSnake->render();
		//Update screen 
		SDL_RenderPresent(gRenderer);
		gSnake->move();
	}

	//Free resources and close SDL
	delete gSnake;
	delete headTexture;
	destroySDL();
	printf("[TRACE] Exiting...");
	return 0;
}


