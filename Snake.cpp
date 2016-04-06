#include"Snake.h"

Snake::Snake(GameTexture* snakeTexture, int x, int y){
	mSpeed = 2;
	mSnakeLenght = 1;
	mChainRadius = mSpriteStepPx;
	mSnakeChain.reserve(5);
	mSnakeTexture = snakeTexture;
	initSpriteClips();
	Chain headChain;
	headChain.bodyRect = &mSpriteClips[0];
	headChain.x = x;
	headChain.y = y;
	headChain.dir = RIGHT;
	mSnakeChain.push_back(headChain); 
}

void Snake::render() {
	for (int i = mSnakeLenght - 1; i > 0; --i) {
		mSnakeTexture->render(mSnakeChain[i].x, mSnakeChain[i].y, mSnakeChain[i].bodyRect);
	}
	switch (mSnakeChain[0].dir) {
	case LEFT:
		mSnakeTexture->render(mSnakeChain[0].x, mSnakeChain[0].y, mSnakeChain[0].bodyRect, 0.0, SDL_FLIP_HORIZONTAL);
		break;
	case RIGHT:
		mSnakeTexture->render(mSnakeChain[0].x, mSnakeChain[0].y, mSnakeChain[0].bodyRect);
		break;
	case UP:
		mSnakeTexture->render(mSnakeChain[0].x, mSnakeChain[0].y, mSnakeChain[0].bodyRect, -90.0);
		break;
	case DOWN:
		mSnakeTexture->render(mSnakeChain[0].x, mSnakeChain[0].y, mSnakeChain[0].bodyRect, 90.0);
		break;
	}
}

Snake::~Snake() {
}

bool Snake::isCollide()
{
	return false;
}

int Snake::addBodyChain()
{
	Chain bodyChain;
	bodyChain.bodyRect = &mSpriteClips[3];
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

void Snake::changeChainDirection(Chain& bodyChain, TurnEvent* nextTurnState, int chainNumber, Chain& nextChain){
	bodyChain.dir = nextTurnState->dir;
	moveDirection(bodyChain);
	if (chainNumber < mSnakeLenght - 1) {
		bodyChain.pathHistory.push(new TurnEvent{ bodyChain.x, bodyChain.y, bodyChain.dir });
	}
	delete nextTurnState;
	nextChain.pathHistory.pop();
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
							changeChainDirection(mSnakeChain[i], nextTurnState, i, mSnakeChain[i - 1]);
						}
						break;
					case RIGHT:
						if (mSnakeChain[i].x != nextTurnState->x) {
							mSnakeChain[i].x += mSpeed;
						}
						else {
							changeChainDirection(mSnakeChain[i], nextTurnState, i, mSnakeChain[i - 1]);
						}
						break;
					case UP:
						if (mSnakeChain[i].y != nextTurnState->y) {
							mSnakeChain[i].y -= mSpeed;
						}
						else {
							changeChainDirection(mSnakeChain[i], nextTurnState, i, mSnakeChain[i - 1]);
						}
						break;
					case DOWN:
						if (mSnakeChain[i].y != nextTurnState->y) {
							mSnakeChain[i].y += mSpeed;
						}
						else {
							changeChainDirection(mSnakeChain[i], nextTurnState, i, mSnakeChain[i - 1]);
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
	if (newDirection == mSnakeChain[0].dir) {
		return true;
	}
	if (!mSnakeChain[0].pathHistory.empty() && mSnakeChain[0].x == mSnakeChain[0].pathHistory.back()->x && mSnakeChain[0].y == mSnakeChain[0].pathHistory.back()->y) {
		return false;
	}
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
		return new TurnEvent{ bodyItem.x, bodyItem.y, bodyItem.dir }; //TODO: this is memory leak!
	}
}

void Snake::initSpriteClips(){
	//Snake's head
	mSpriteClips[0].x = 0;
	mSpriteClips[0].y = 0;
	mSpriteClips[0].w = mSpriteStepPx;
	mSpriteClips[0].h = mSpriteStepPx;

	//Snake's body chain outer
	mSpriteClips[1].x = 50;
	mSpriteClips[1].y = 0;
	mSpriteClips[1].w = mSpriteStepPx;
	mSpriteClips[1].h = mSpriteStepPx;

	//Snake's body chain outer
	mSpriteClips[2].x = 100;
	mSpriteClips[2].y = 0;
	mSpriteClips[2].w = mSpriteStepPx;
	mSpriteClips[2].h = mSpriteStepPx;

	//Snake's body chain outer
	mSpriteClips[3].x = 150;
	mSpriteClips[3].y = 0;
	mSpriteClips[3].w = mSpriteStepPx;
	mSpriteClips[3].h = mSpriteStepPx;

	//Snake's body chain outer
	mSpriteClips[4].x = 200;
	mSpriteClips[4].y = 0;
	mSpriteClips[4].w = mSpriteStepPx;
	mSpriteClips[4].h = mSpriteStepPx;

}

