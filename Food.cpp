#include "Food.h"

Food::Food(const GameObjectType goType) : iam(goType)
{
	x = 0;
	y = 0;
}

Food::Food()
{
	switch (rand() % 4) {
	case 0:
		iam = FOOD_APPLE;
		break;
	case 1:
		iam = FOOD_CARROT;
		break;
	case 2:
		iam = FOOD_LEAF;
		break;
	case 3:
		iam = FOOD_POTATO;
		break;
	}
}


Food::~Food()
{
}

void Food::init(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Food::applyGameEvent(const GameEvent gEvent)
{
}

void Food::move()
{
}

std::vector<DrawConstruct> Food::getDrawConstruct() const
{
	std::vector<DrawConstruct> dc;
	dc.push_back({ iam, x, y, Direction::NONE });
	return dc;
}
