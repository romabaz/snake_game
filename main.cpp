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
		x = double(radius)*cos(radVal) + double(centerX);
		y = double(radius)*sin(radVal) + double(centerY);
		SDL_RenderDrawPoint(renderer, x, y);
	}
	return;
}

int main(int argc, char* args[]){
	
	printf("[TRACE] Snake has started\n");

	GameWorld gw;
	Snakey snakeyAlpha;
	gw.put(&snakeyAlpha);

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
					++quit;
					break;
				case SDLK_w:
					break;
				case SDLK_s:
					break;
				case SDLK_f:
					break;
				case SDLK_UP:
					//gSnake->setDirection(UP);
					break;
				case SDLK_DOWN:
					//gSnake->setDirection(DOWN);
					break;
				case SDLK_LEFT:
					//gSnake->setDirection(LEFT);
					break;
				case SDLK_RIGHT:
					printf("RIGHT!");
					break;
				case SDLK_SPACE:
					printf("Space!");
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&currMouseX, &currMouseY);
				break;
			}
		}
		//Track mouse
		//SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
		//drawCircle(gRenderer, currMouseX, currMouseY, 7);
		gw.draw();
		gw.tick(e);
		
	}

	printf("[TRACE] Exiting...");
	return 0;
}


