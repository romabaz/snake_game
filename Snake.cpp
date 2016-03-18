#include"Snake.h"

Snake::Snake(Chain headChain){
	mSpeed = 1;
	mSnakeLenght = 1;
	mChainRadius = 10;
	mSnakeChain.reserve(5);
	mSnakeChain.push_back(headChain); 
	mCurrentDirection = RIGHT;
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
	switch (mSnakeChain[mSnakeLenght - 1].dir) {
	case LEFT:
		bodyChain.x = mSnakeChain[mSnakeLenght - 1].x + mChainRadius;
		bodyChain.y = mSnakeChain[mSnakeLenght - 1].y;
		break;
	case RIGHT:
		bodyChain.x = mSnakeChain[mSnakeLenght - 1].x - mChainRadius;
		bodyChain.y = mSnakeChain[mSnakeLenght - 1].y;
		break;
	case UP:
		bodyChain.x = mSnakeChain[mSnakeLenght - 1].x;
		bodyChain.y = mSnakeChain[mSnakeLenght - 1].y + mChainRadius;
		break;
	case DOWN:
		bodyChain.x = mSnakeChain[mSnakeLenght - 1].x;
		bodyChain.y = mSnakeChain[mSnakeLenght - 1].y - mChainRadius;
		break;
	}
	bodyChain.dir = mSnakeChain[mSnakeLenght - 1].dir;
	mSnakeChain.push_back(bodyChain);
	return ++mSnakeLenght;
}

SDL_Point Snake::move()
{
	if (!isCollide()) {
		if (mSnakeLenght > 1) {
			for (int i = mSnakeLenght - 1; i > 0; --i) {
				mSnakeChain[i].x = mSnakeChain[i - 1].x;
				mSnakeChain[i].y = mSnakeChain[i - 1].y;
				mSnakeChain[i].dir = mSnakeChain[i - 1].dir;
			}
		}
		switch (mCurrentDirection) {
		case LEFT:
			mSnakeChain[0].x -= mSpeed;
			break;
		case RIGHT:
			mSnakeChain[0].x += mSpeed;
			break;
		case UP:
			mSnakeChain[0].y -= mSpeed;
			break;
		case DOWN:
			mSnakeChain[0].y += mSpeed;
			break;
		}
	}
	return {mSnakeChain[0].x, mSnakeChain[0].y};
}


bool Snake::setDirection(Directions newDirection) 
{
	mCurrentDirection = newDirection;
	mSnakeChain[0].dir = mCurrentDirection;
	return !isCollide();
}

void Snake::setSpeed(short newSpeed) 
{
	mSpeed = newSpeed;
}

short Snake::getSpeed() {
	return mSpeed;
}