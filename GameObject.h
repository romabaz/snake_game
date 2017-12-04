#pragma once
#include "GlobalTypes.h"
class GameObject {
public:
	virtual int tick(const GameEvent& gEvent) = 0;
	virtual void init(int x, int y) = 0;

private:
	//pointer to the function performing drawing to the game field
	static void(*drawFuncPtr)(int, int, const GameObject&);
	
	//current position
	int x = 0;
	int y = 0;

	//radius
	static const int radius = 35;
};
