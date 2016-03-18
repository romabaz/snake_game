#include"Snake.h"

Snake::Snake(Chain headChain){
	mSpeed = 1;
	mSnakeLenght = 1;
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

SDL_Point Snake::move()
{
	if (!isCollide()) {
		if (mSnakeLenght > 1) {
			for (int i = mSnakeLenght - 1; i > 0; --i) {
				mSnakeChain[i].x = mSnakeChain[i - 1].x;
				mSnakeChain[i].y = mSnakeChain[i - 1].y;
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
	return SDL_Point();
}


bool Snake::setDirection(Directions newDirection) 
{
	mCurrentDirection = newDirection;
	return !isCollide();
}

void Snake::setSpeed(short newSpeed) 
{
	mSpeed = newSpeed;
}

short Snake::getSpeed() {
	return mSpeed;
}