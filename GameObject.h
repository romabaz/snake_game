#pragma once
#include<vector>
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
	GE_GROW,
	GE_NONE
} GameEvent;

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
} Direction;

struct DrawConstruct {
	GameObjectType type;
	int x;
	int y;
	Direction dir;
};

class GameObject {
protected:
	//todo: tightly coupled with GameTexture.mSpriteStepPx
	static const int radius = 50;

public:
	virtual void applyGameEvent(const GameEvent gEvent) = 0;
	inline void applyGameEvent() {
		applyGameEvent(GE_NONE);
	};
	virtual void move() = 0;
	virtual void init(int x, int y) = 0;
	virtual std::vector<DrawConstruct> getDrawConstruct() const = 0;
	virtual const GameObjectType getType() const = 0;
};
