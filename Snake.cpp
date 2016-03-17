#include"Snake.h"

Snake::Snake(int startX, int startY, Chain headChain) : mSnakeChain(5){
	mXHead = startX;
	mYHead = startY;
	mSnakeLenght = 1;
	mSnakeChain.push_back(headChain);
	currentDirection = RIGHT;
}

void Snake::render(){
	for (int i = mSnakeChain.size() - 1; i >= 0; i--){
		mSnakeChain[i].bodyTexture->render(mSnakeChain[i].x, mSnakeChain[i].y);
	}
}