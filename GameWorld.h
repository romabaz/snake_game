#pragma once
#include<SDL.h>
#include"GameObject.h"
#include"GameTexture.h"
#include<stdio.h>
#include<vector>

class GameWorld {
public:
	GameWorld();
	~GameWorld();

	void tick(const SDL_Event& sdlEvent);
	void put(GameObject* gameObject);
	void draw();

private:
	short initGraphicSystem();
	short initSDL();
	short initSDLRenderer();
	short initGameTexture();
	void destroySDL();
	

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
};

