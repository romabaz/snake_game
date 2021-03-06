#pragma once
#include "GameObject.h"
class Food :
	public GameObject
{
public:
	Food(const GameObjectType goType);
	Food();
	~Food();

	void init(int x, int y) override;
	void applyGameEvent(const GameEvent gEvent) override;
	void move() override;
	std::vector<DrawConstruct> getDrawConstruct() const override;
	inline const GameObjectType getType() const override { return iam; }
	inline const CollisionZone getCollisionZone() const override {
		return{ {x - radius, y - radius}, 2 * radius, 2 * radius };
	};

private:
	GameObjectType iam;
	int x;
	int y;
};

