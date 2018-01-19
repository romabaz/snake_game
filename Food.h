#pragma once
#include "GameObject.h"
class Food :
	public GameObject
{
public:
	Food();
	~Food();

	void init(int x, int y) override;
	void applyGameEvent(const GameEvent gEvent) override;
	void move() override;
	std::vector<DrawConstruct> getDrawConstruct() const override;
	inline const GameObjectType getType() const override { return iam; }

private:
	GameObjectType iam;
	int x;
	int y;
};

