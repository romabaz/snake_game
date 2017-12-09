#pragma once
#include "GlobalTypes.h"
class GameObject {
protected:
	typedef enum Directions {
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NONE
	} Direction;

	//pointer to the function performing drawing to the game field
	static void(*drawFuncPtr)(const GameObject* gameObject);

	//radius
	static const int radius = 35;

public:
	virtual void tick(const GameEvent& gEvent) = 0;
	virtual void init(int x, int y, Direction dir) = 0;

};
