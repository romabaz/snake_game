#include "Snakey.h"



Snakey::Snakey()
{
	//set initial capacity
	mSnakeyBody.reserve(8);
	//create snakey's head
	mSnakeyBody.push_back(new SnakeyQuantum(0, 0, NONE));
}


Snakey::~Snakey()
{
	//1. Traverse mSnakeyBody and delete all SnakeyQuantum objects
	//2. Traverse mSnakeyEventQueue and delete all SnakeyEvent objects
}


void Snakey::init(int x, int y, Direction dir) 
{
	for (SnakeyQuantum* sq : mSnakeyBody) {
		if (sq != nullptr) {
			sq->x = x;
			sq->y = y;
			sq->direction = dir;
		}
		else {
			throw std::invalid_argument("NULL pointer in snakey body");
		}
	}

}

void Snakey::tick(const GameEvent& gEvent)
{
	//1. Applied event to head
	//2. Moved head in the new direction
	//3. Moved all body in the consequent direction
	//4. Added SnakeEvent to the queue
	SnakeyQuantum* snakeHead = mSnakeyBody.at(0);
	if (snakeHead != nullptr) {
		switch(gEvent) {
		case GE_UP:
			break;
		case GE_DOWN:
			break;
		case GE_LEFT:
			break;
		case GE_RIGHT:
			break;
		default:
			//nothing
		}
		
	}
	for (SnakeyQuantum* sq : mSnakeyBody) {
		if (sq != nullptr) {
			
		}
		else {
			throw std::invalid_argument("NULL pointer in snakey body");
		}
	}
}

void Snakey::draw()
{
	drawFuncPtr(this);
}
