#pragma once
#include "GlobalTypes.h"
class GameObject {
protected:
	typedef enum {
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
	virtual void tick(GameEvent gEvent) = 0;
	inline virtual void tick() {
		tick(GE_NONE);
	};
	virtual void init(int x, int y, Direction dir) = 0;

};
