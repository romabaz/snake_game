#pragma once
#include<SDL.h>
#include"GameObject.h"
#include"GameTexture.h"
#include<stdio.h>
#include<vector>
#include <time.h>

class GameWorld {
public:
	GameWorld();
	~GameWorld();

	void tick();
	void propagate(const SDL_Event& sdlEvent);
	void put(GameObject* gameObject, bool random = false);
	void draw();

private:
	short initGraphicSystem();
	short initSDL();
	short initSDLRenderer();
	short initGameTexture();
	void destroySDL();

	GameEvent covertSDLEventToGameEvent(const SDL_Event sdlEvent);
	

    //path to default texture
	const char* defaultTexturePath = "snake_ss2.bmp";

	
	//SDL rendering entities
	SDL_Window* gWindow = nullptr;
	SDL_Renderer* gRenderer = nullptr;
	bool sdlExists = false;
	GameTexture* texture;

	//Basic coordinates
	const int SCREEN_WIDTH = 1500;
	const int SCREEN_HEIGHT = 800;

	std::vector<GameObject*> gameObjects;

	GameObject* snakeyObject;
};

