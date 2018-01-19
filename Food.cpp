#include "Food.h"



Food::Food()
{
}


Food::~Food()
{
}

void Food::init(int x, int y)
{
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
