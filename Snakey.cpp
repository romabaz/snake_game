#include "Snakey.h"

Snakey::Snakey(): mSnakeyLength(1), mSpeed(1)
{
	//set initial capacity
	mSnakeyBody.reserve(8);
	//create snakey's head
	mSnakeyBody.push_back(new SnakeyQuantum(0, 0, LEFT, SNAKEY_HEAD));
}


Snakey::~Snakey()
{
	//1. Traverse mSnakeyBody and delete all SnakeyQuantum objects
	//2. Traverse mSnakeyEventQueue and delete all SnakeyEvent objects
}

//fixme - wrong implementation. need to think about purpose and design of it
void Snakey::init() 
{
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
		bool eventAdded = false;
		if (gEvent != GE_NONE) {
			mSnakeyEvents.push_back(new SnakeyEvent(eventX, eventY, gEvent));
			eventAdded = true;
		}
		for (std::size_t i = 1; i < mSnakeyLength; i++) {
			SnakeyQuantum* sq = mSnakeyBody[i];
			if (mSnakeyEvents.size() < 1) {
				//no events in vector. Just move forward
				move(sq);
			}
			else {
				//Safe check - we shouldn't get into this trouble
				if (sq->nextSnakeyEventId > mSnakeyEvents.size() - 1) {
					throw std::out_of_range("Quantum state is broken: the next snakey event is out of range");
				}

				//Quantum is ready for the next incoming event
				if (sq->nextSnakeyEventId == -1) {
					if (eventAdded) {
						sq->nextSnakeyEventId++;
					} else continue;
				}
				
				//1. Check each quantum for its event to happen
				SnakeyEvent* nextSEvent = mSnakeyEvents[sq->nextSnakeyEventId];
				if (sq->x == nextSEvent->x &&
					sq->y == nextSEvent->y) {

					//2. Apply event
					applyGameEvent(sq, nextSEvent->event);

					//3. Reset or move forward the nextEventId
					if (nextSEvent == mSnakeyEvents.back()) {
						//No events left for this quantum
						sq->nextSnakeyEventId = -1;
					}
					else {
						//set the next event for this quantum
						sq->nextSnakeyEventId++;
					}

					//4. Delete SnakeyEvent if this is the last quantum
					if (i == mSnakeyLength - 1) {
						mSnakeyEvents.pop_front();
						delete nextSEvent;
					}
					
				}
			}
		}
	}

}

const GameObjectType Snakey::getType() const
{
	return iam;
}

int Snakey::getXPosition() const
{
	return mSnakeyBody.front()->x;
}

int Snakey::getYPosition() const
{
	return mSnakeyBody.front()->y;
}

void Snakey::grow()
{
	SnakeyQuantum* lastQuantum = mSnakeyBody.back();
	int x = 0, y = 0;
	switch (lastQuantum->direction) {
	case LEFT:
		x = lastQuantum->x + radius;
		y = lastQuantum->y;
		break;
	case RIGHT:
		x = lastQuantum->x - radius;
		y = lastQuantum->y;
		break;
	case UP:
		x = lastQuantum->x;
		y = lastQuantum->y + radius;
		break;
	case DOWN:
	default:
		x = lastQuantum->x;
		y = lastQuantum->y - radius;
		break;
	}
	mSnakeyBody.push_back(new SnakeyQuantum(x, y, lastQuantum->direction, SNAKEY_QUANTUM1));
	++mSnakeyLength;
}

void Snakey::draw()
{
	for (SnakeyQuantum* quantum : mSnakeyBody) {
		gameWorld->drawFunction(quantum->iam, quantum->x, quantum->y);
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

