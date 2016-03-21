#include"Snake.h"

Snake::Snake(GameTexture* headTexture, int x, int y){
	mSpeed = 1;
	mSnakeLenght = 1;
	mChainRadius = 10;
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

/*
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
*/

SDL_Point Snake::move()
{
	if (!isCollide()) {
		if (mSnakeLenght > 1) {
			for (int i = 1; i < mSnakeLenght - 1; ++i) {
				if (mSnakeChain[i].xApplyDir == mSnakeChain[i - 1].x) {
					mSnakeChain[i].xApplyDir = -1;
					mSnakeChain[i].dir = mSnakeChain[i].newDir;
					mSnakeChain[i + 1].xApplyDir = mSnakeChain[i].x;
					mSnakeChain[i + 1].newDir = mSnakeChain[i].dir;
				}
				if (mSnakeChain[i].yApplyDir == mSnakeChain[i - 1].y) {
					mSnakeChain[i].yApplyDir = -1;
					mSnakeChain[i].dir = mSnakeChain[i].newDir;
					mSnakeChain[i + 1].yApplyDir = mSnakeChain[i].y;
					mSnakeChain[i + 1].newDir = mSnakeChain[i].dir;
				}
				switch (mSnakeChain[i].dir) {
				case LEFT:
					mSnakeChain[i].x -= mSpeed;
					break;
				case RIGHT:
					mSnakeChain[i].x += mSpeed;
					break;
				case UP:
					mSnakeChain[i].y -= mSpeed;
					break;
				case DOWN:
					mSnakeChain[i].y += mSpeed;
					break;
				}
				mSnakeChain[i].x -= mSpeed;
				mSnakeChain[i].y += mSpeed;
				mSnakeChain[i].dir = mSnakeChain[i - 1].dir;
			}
		}
		switch (mSnakeChain[0].dir) {
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
	return{ mSnakeChain[0].x, mSnakeChain[0].y };
}

bool Snake::setDirection(Directions newDirection) 
{
	if (mSnakeLenght > 1) {
		switch (newDirection) {
		case LEFT:
		case RIGHT:
			mSnakeChain[1].yApplyDir = mSnakeChain[0].y;
			break;
		case UP:
		case DOWN:
			mSnakeChain[1].xApplyDir = mSnakeChain[0].x;
			break;
		}
		mSnakeChain[1].newDir = newDirection;
	}
	mSnakeChain[0].dir = newDirection;
	return !isCollide();
}

void Snake::setSpeed(short newSpeed) 
{
	mSpeed = newSpeed;
}

short Snake::getSpeed() {
	return mSpeed;
}