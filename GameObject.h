#pragma once
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

	//todo: tightly coupled with GameTexture.mSpriteStepPx
	static const int radius = 50;

public:
	virtual void tick(GameEvent gEvent) = 0;
	inline void tick() {
		tick(GE_NONE);
	};
	virtual void init(int x, int y, Direction dir) = 0;

};
