#include "Food.h"

Food::Food(const GameObjectType goType) : iam(goType)
{
	x = 0;
	y = 0;
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
