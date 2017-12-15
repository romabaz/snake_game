#pragma once
#include<SDL.h>
#include"GameObject.h"
class GameWorld {
private:
	void drawFunction(const GameObject* gameObject);

public:
	GameWorld();
	~GameWorld();

	void tick(const SDL_Event& sdlEvent);
	void put(const GameObject& gameObject);
};

