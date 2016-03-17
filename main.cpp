#include<stdio.h>
#include<SDL.h>

//SDL rendering entities
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//Basic coordinates
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 800;

const int ZERO_X = 100;
const int ZERO_Y = 700;


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

int main(int argc, char* args[]){
	
	printf("[TRACE] Chart has started\n");
	if (!initGraphics()){
		printf("[TRACE] Exiting...");
		return 0;
	}


	short quit = 0;
	SDL_Event e;
	int mouseX = 0, mouseY = 0;

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
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mouseX, &mouseY);
				if (mousePoints(mouseX, mouseY)){
					//textTexture = renderTexture(message, textColor);
					printf("X:%d,Y:%d\n", mouseX, mouseY);
				}
				else {
					//SDL_DestroyTexture(textTexture);
					//textTexture = NULL;
				}
				break;
			}
		}
		//Clear screen '
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		//Draw coordinate lines
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawLine(gRenderer, ZERO_X, ZERO_Y, SCREEN_WIDTH - ZERO_X, ZERO_Y);
		SDL_RenderDrawLine(gRenderer, ZERO_X, ZERO_Y, ZERO_X, SCREEN_HEIGHT - ZERO_Y);

		//Update screen 
		SDL_RenderPresent(gRenderer);
	}

	//Free resources and close SDL
	destroySDL();
	printf("[TRACE] Exiting...");
	return 0;
}


