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

	SnakeyQuantum* snakeHead = mSnakeyBody[0];
	int eventX = snakeHead->x;
	int eventY = snakeHead->y;

	//Apply to head first
	applyGameEvent(snakeHead, gEvent);
	if (mSnakeyLength > 1) {
		//Add SnakeyEvent to the vector if the event has happenned
		if (gEvent != GE_NONE) {
			mSnakeyEvents.push_back(new SnakeyEvent(eventX, eventY, gEvent));
		}
		for (std::size_t i = 1; i < mSnakeyLength; i++) {
			SnakeyQuantum* sq = mSnakeyBody[i];
			if (mSnakeyEvents.size() < 1) {
				//no events in vector. Just move forward
				move(sq);
			}
			else {
				//1. Check each quantum for its event to happen
				SnakeyEvent* nextSEvent = mSnakeyEvents[sq->nextSnakeyEventId];
				if (sq->x == nextSEvent->x &&
					sq->y == nextSEvent->y) {
					//2. Apply event
					applyGameEvent(sq, nextSEvent->event);
					//3. Reset or move forward the nextEventId
					if (nextSEvent == mSnakeyEvents.back()) {
						//No events left for this quantum
						sq->nextSnakeyEventId = 0;
					}
					else {
						//set the next event for this quantum
						sq->nextSnakeyEventId++;
					}
					//4. Delete SnakeyEvent if this is the last quantum
					if (i == mSnakeyLength - 1) {
						mSnakeyEvents.pop_front();
						//mSnakeyEvents.remove(nextSEvent); need to check this simpler solution
						delete nextSEvent;
					}
					
				}
			}
		}
	}

}

void Snakey::draw()
{
	drawFuncPtr(this);
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

std::size_t Snakey::findNextSnakeyEvent(const SnakeyEvent* currentEvent)
{
	std::size_t eventLen = mSnakeyEvents.size();
	std::size_t currentId = eventId;
	while (currentId < eventLen) {
		if (mSnakeyEvents[currentId] != 0) {
			return currentId;
		}
		else {
			currentId++;
		}
	}
	return 0;
}
