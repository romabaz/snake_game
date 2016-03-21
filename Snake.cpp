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
				if (mSnakeChain[i].dir != mSnakeChain[i - 1].dir)  {
					switch (mSnakeChain[i].dir) {
					case LEFT:
						if (mSnakeChain[i].x != mSnakeChain[i - 1].x) {
							mSnakeChain[i].x -= mSpeed;
						}
						else {
							mSnakeChain[i].dir = mSnakeChain[i - 1].dir;
							moveDirection(mSnakeChain[i]);
						}
						break;
					case RIGHT:
						if (mSnakeChain[i].x != mSnakeChain[i - 1].x) {
							mSnakeChain[i].x += mSpeed;
						}
						else {
							mSnakeChain[i].dir = mSnakeChain[i - 1].dir;
							moveDirection(mSnakeChain[i]);
						}
						break;
					case UP:
						if (mSnakeChain[i].y != mSnakeChain[i - 1].y) {
							mSnakeChain[i].y -= mSpeed;
						}
						else {
							mSnakeChain[i].dir = mSnakeChain[i - 1].dir;
							moveDirection(mSnakeChain[i]);
						}
						break;
					case DOWN:
						if (mSnakeChain[i].y != mSnakeChain[i - 1].y) {
							mSnakeChain[i].y += mSpeed;
						}
						else {
							mSnakeChain[i].dir = mSnakeChain[i - 1].dir;
							moveDirection(mSnakeChain[i]);
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
	return{ mSnakeChain[0].x, mSnakeChain[0].y };
}

void Snake::moveDirection(Chain& bodyItem) {
	switch (bodyItem.dir) {
	case LEFT:
		bodyItem.x -= mSpeed;
		break;
	case RIGHT:
		bodyItem.x += mSpeed;
		break;
	case UP:
		bodyItem.y -= mSpeed;
		break;
	case DOWN:
		bodyItem.y += mSpeed;
		break;
	}
}

bool Snake::setDirection(Directions newDirection) 
{
	if (!isCollide()) {
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