#include"Snake.h"

Snake::Snake(GameTexture* headTexture, int x, int y){
	mSpeed = 1;
	mSnakeLenght = 1;
	mChainRadius = 50;
	mSnakeChain.reserve(5);
	Chain headChain;
	headChain.bodyTexture = headTexture;
	headChain.x = x;
	headChain.y = y;
	headChain.dir = RIGHT;
	mSnakeChain.push_back(headChain); 
}

void Snake::render(){
	for (int i = mSnakeLenght - 1; i >= 0; --i){
		mSnakeChain[i].bodyTexture->render(mSnakeChain[i].x, mSnakeChain[i].y);
	}
}

bool Snake::isCollide()
{
	return false;
}

int Snake::addBodyChain(GameTexture* bodyTexure)
{
	Chain bodyChain;
	bodyChain.bodyTexture = bodyTexure;
	Chain lastChain = mSnakeChain[mSnakeLenght - 1];
	switch (lastChain.dir) {
	case LEFT:
		bodyChain.x = lastChain.x + mChainRadius;
		bodyChain.y = lastChain.y;
		break;
	case RIGHT:
		bodyChain.x = lastChain.x - mChainRadius;
		bodyChain.y = lastChain.y;
		break;
	case UP:
		bodyChain.x = lastChain.x;
		bodyChain.y = lastChain.y + mChainRadius;
		break;
	case DOWN:
		bodyChain.x = lastChain.x;
		bodyChain.y = lastChain.y - mChainRadius;
		break;
	}
	bodyChain.dir = lastChain.dir;
	mSnakeChain.push_back(bodyChain);
	return ++mSnakeLenght;
}


void Snake::move()
{
	if (!isCollide()) {
		if (mSnakeLenght > 1) {
			for (int i = mSnakeLenght - 1; i > 0; --i) {
				TurnEvent* nextTurnState = readNextTurnState(mSnakeChain[i - 1]);
				if (mSnakeChain[i].dir != nextTurnState->dir)  {
					switch (mSnakeChain[i].dir) {
					case LEFT:
						if (mSnakeChain[i].x != nextTurnState->x) {
							mSnakeChain[i].x -= mSpeed;
						}
						else {
							mSnakeChain[i].pathHistory.push(new TurnEvent{ mSnakeChain[i].x, mSnakeChain[i].y, nextTurnState->dir });
							mSnakeChain[i].dir = nextTurnState->dir;
							moveDirection(mSnakeChain[i]);
							mSnakeChain[i - 1].pathHistory.pop();
						}
						break;
					case RIGHT:
						if (mSnakeChain[i].x != nextTurnState->x) {
							mSnakeChain[i].x += mSpeed;
						}
						else {
							mSnakeChain[i].pathHistory.push(new TurnEvent{ mSnakeChain[i].x, mSnakeChain[i].y, nextTurnState->dir });
							mSnakeChain[i].dir = nextTurnState->dir;
							moveDirection(mSnakeChain[i]);
							mSnakeChain[i - 1].pathHistory.pop();
						}
						break;
					case UP:
						if (mSnakeChain[i].y != nextTurnState->y) {
							mSnakeChain[i].y -= mSpeed;
						}
						else {
							mSnakeChain[i].pathHistory.push(new TurnEvent{ mSnakeChain[i].x, mSnakeChain[i].y, nextTurnState->dir });
							mSnakeChain[i].dir = nextTurnState->dir;
							moveDirection(mSnakeChain[i]);
							mSnakeChain[i - 1].pathHistory.pop();
						}
						break;
					case DOWN:
						if (mSnakeChain[i].y != nextTurnState->y) {
							mSnakeChain[i].y += mSpeed;
						}
						else {
							mSnakeChain[i].pathHistory.push(new TurnEvent{ mSnakeChain[i].x, mSnakeChain[i].y, nextTurnState->dir });
							mSnakeChain[i].dir = nextTurnState->dir;
							moveDirection(mSnakeChain[i]);
							mSnakeChain[i - 1].pathHistory.pop();
						}
						break;
					}
				}
				else {
					moveDirection(mSnakeChain[i]);
				}
			}
		}
		//move Head
		moveDirection(mSnakeChain[0]);
	}
	return;
}

void Snake::moveDirection(Chain& itemChain) {
	switch (itemChain.dir) {
	case LEFT:
		itemChain.x -= mSpeed;
		break;
	case RIGHT:
		itemChain.x += mSpeed;
		break;
	case UP:
		itemChain.y -= mSpeed;
		break;
	case DOWN:
		itemChain.y += mSpeed;
		break;
	}
}

bool Snake::setDirection(Directions newDirection) 
{
	if (!isCollide()) {
		if (mSnakeLenght > 1) {
			mSnakeChain[0].pathHistory.push(new TurnEvent{ mSnakeChain[0].x, mSnakeChain[0].y, newDirection });
		}
		mSnakeChain[0].dir = newDirection;
		return true;
	}
	else {
		return false;
	}
}

void Snake::setSpeed(short newSpeed) 
{
	mSpeed = newSpeed;
}

short Snake::getSpeed() {
	return mSpeed;
}


TurnEvent* Snake::readNextTurnState(Chain& bodyItem){
	if (bodyItem.pathHistory.size() > 0) {
		return bodyItem.pathHistory.front();
	}
	else {
		return new TurnEvent{ bodyItem.x, bodyItem.y, bodyItem.dir };
	}
}


