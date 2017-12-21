#pragma once
#include<SDL.h>
#include"GameObject.h"
#include"GameTexture.h"
#include<stdio.h>
#include<map>
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
	void destroySDL();

	//SDL rendering entities
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	bool sdlExists = false;

	//Basic coordinates
	const int SCREEN_WIDTH = 1500;
	const int SCREEN_HEIGHT = 800;

	std::map<const GameObject&, const GameTexture&> texturedObject;
};

