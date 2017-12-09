#include "Snakey.h"

Snakey::Snakey()
{
	//set initial capacity
	mSnakeyBody.reserve(8);
	//create snakey's head
	mSnakeyBody.push_back(new SnakeyQuantum(0, 0, NONE));
	mSnakeyLength = 1;
	mSpeed = 1;
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

void Snakey::tick(GameEvent gEvent)
{
	SnakeyQuantum* snakeHead = mSnakeyBody.at(0);
	if (snakeHead != nullptr) {
		if (mSnakeyLength > 1) {
			//Add SnakeEvent to the queue
			mSnakeyEventQueue.push(new SnakeyEvent(snakeHead->x, snakeHead->y, gEvent));
			SnakeyEvent* nextSnakeyEvent = mSnakeyEventQueue.front();
		}
		//Apply event to head
		//Move head in the new direction
		switch(gEvent) {
		case GE_UP:
			snakeHead->direction = UP;
			snakeHead->y -= mSpeed;
			break;
		case GE_DOWN:
			snakeHead->direction = DOWN;
			snakeHead->y -= mSpeed;
			break;
		case GE_LEFT:
			snakeHead->direction = LEFT;
			snakeHead->x -= mSpeed;
			break;
		case GE_RIGHT:
			snakeHead->direction = RIGHT;
			snakeHead->x += mSpeed;
			break;
		default:
			//nothing
		}

	}
	else {
		throw std::invalid_argument("Snake head is nullptr");
	}
	//Move all body in the consequent direction
	for (std::size_t i = 1; i < mSnakeyLength; i++) {
		SnakeyQuantum* sq = mSnakeyBody.at(i);
		
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
