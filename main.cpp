#include<stdio.h>
#include<math.h>
#include"Snakey.h"
#include"GameWorld.h"

#define PI 3.14159265359


const int ZERO_X = 100;
const int ZERO_Y = 700;


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

	/*
	if (!initGraphics()){
		printf("[TRACE] Exiting...");
		return 0;
	}
	

	GameTexture* snakeTexture = new GameTexture(gRenderer);
	if (!snakeTexture->load("snake_ss2.bmp")) {
		printf("[ERROR] Cannot load snake's head. Exiting...\n");
		destroySDL();
		delete snakeTexture;
		return 0;
	}
	
	gSnake = new Snake(snakeTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);*/
	GameWorld gw;
	Snakey snakeyAlpha;
	gw.put(snakeyAlpha);




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
				case SDLK_f:
					//TODO: add food
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
					gSnake->addBodyChain();
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
		//SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
		//drawCircle(gRenderer, currMouseX, currMouseY, 7);

		gSnake->renderFood(150, 150, 5);

		//render snake
		gSnake->render();
		
		//Update screen 
		SDL_RenderPresent(gRenderer);
		gSnake->move();
	}

	//Free resources and close SDL
	delete snakeTexture;
	delete gSnake;
	destroySDL();
	printf("[TRACE] Exiting...");
	return 0;
}


