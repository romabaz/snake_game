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

//fixme - wrong implementation. need to think about purpose and design of it
void Snakey::init(int x, int y, Direction dir) 
{
	for (SnakeyQuantum* sq : mSnakeyBody) {
		if (sq != nullptr) {
			sq->x += x;
			sq->y += y;
		}
		else {
			throw std::invalid_argument("NULL pointer in snakey body");
		}
	}

}

void Snakey::tick(GameEvent gEvent)
{
	if (mSnakeyLength < 1) {
		return;
	}

	SnakeyQuantum* snakeHead = mSnakeyBody.at(0);
	int eventX = snakeHead->x;
	int eventY = snakeHead->y;

	//Apply to head first
	applyGameEvent(snakeHead, gEvent);
	if (mSnakeyLength > 1) {
		//Add SnakeyEvent to the queue
		mSnakeyEventQueue.push(new SnakeyEvent(eventX, eventY, gEvent));
		//Apply the next event in the queue to the rest of the snake
		applySnakeyEvent(mSnakeyEventQueue.front());
	}

}

void Snakey::draw()
{
	drawFuncPtr(this);
}


//todo: rethink of this design
void Snakey::move(SnakeyQuantum* sq)
{
	switch (sq->direction)
	{
	case UP:
		sq->y -= mSpeed;
		break;
	case DOWN:
		sq->y += mSpeed;
		break;
	case LEFT:
		sq->x -= mSpeed;
		break;
	case RIGHT:
		sq->x += mSpeed;
		break;
	default:
		break;
	}
}

void Snakey::applySnakeyEvent(SnakeyEvent* snakeyEvent)
{
	//Move all body in the consequent direction
	for (std::size_t i = 1; i < mSnakeyLength; i++) {
		SnakeyQuantum* sq = mSnakeyBody.at(0);
		if (sq->x == snakeyEvent->x && sq->y == snakeyEvent->y) {
			applyGameEvent(sq, snakeyEvent->event);
			mSnakeyEventQueue.pop();
			if (i < mSnakeyLength - 1) {
				mSnakeyEventQueue.push(snakeyEvent);
			}
			else {
				delete snakeyEvent;
				return;
			}
		}
		else {
			move(sq);
		}
	}
}

void Snakey::applyGameEvent(SnakeyQuantum* sq, GameEvent gameEvent)
{
	switch (gameEvent) {
	case GE_UP:
		sq->direction = UP;
		sq->y -= mSpeed;
		break;
	case GE_DOWN:
		sq->direction = DOWN;
		sq->y -= mSpeed;
		break;
	case GE_LEFT:
		sq->direction = LEFT;
		sq->x -= mSpeed;
		break;
	case GE_RIGHT:
		sq->direction = RIGHT;
		sq->x += mSpeed;
		break;
	case GE_NONE:
		move(sq);
		break;
	default:
		break;
	}
}

