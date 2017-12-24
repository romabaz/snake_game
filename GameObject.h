#pragma once
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

	const GameObjectType iam;

public:
	virtual void tick(GameEvent gEvent) = 0;
	inline void tick() {
		tick(GE_NONE);
	};
	virtual void init(int x, int y, Direction dir) = 0;
	virtual const GameObjectType getType() const = 0;
	virtual int getXPosition() const = 0;
	virtual int getYPosition() const = 0;

};
