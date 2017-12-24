#pragma once
#include<SDL.h>
#include"GameObject.h"
#include<stdio.h>
#include<map>

//todo: is this proper place for such declaration?
typedef enum {
	SNAKEY,
	SNAKEY_HEAD,
	SNAKEY_QUANTUM1,
	SNAKEY_QUANTUM2,
	SNAKEY_QUANTUM3,
	SNAKEY_QUANTUM4,
	FOOD_LEAF,
	FOOD_APPLE,
	FOOD_POTATO,
	FOOD_CARROT
} GameObjectType;

typedef enum {
	GE_LEFT,
	GE_RIGHT,
	GE_UP,
	GE_DOWN,
	GE_NONE
} GameEvent;


class GameWorld {
private:
	void drawFunction(const GameObject* gameObject);

public:
	GameWorld();
	~GameWorld();

	void tick(const SDL_Event& sdlEvent);
	void put(const GameObject& gameObject);

private:
	short initGraphicSystem();
	short initSDL();
	short initSDLRenderer();
	short initGameTexture();
	void destroySDL();

	//path to default texture
	const char* defaultTexturePath = "snake_ss2.bmp";

	
	//SDL rendering entities
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	bool sdlExists = false;

	//Basic coordinates
	const int SCREEN_WIDTH = 1500;
	const int SCREEN_HEIGHT = 800;

	std::map<const GameObject&, const SDL_Texture[]> texturedObject;
};

