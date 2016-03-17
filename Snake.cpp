#include"Snake.h"

Snake::Snake(Chain headChain){
	mXHead = headChain.x;
	mYHead = headChain.y;
	mSnakeLenght = 1;
	mSnakeChain.reserve(5);
	mSnakeChain.push_back(headChain); 
	currentDirection = RIGHT;
}

void Snake::render(){
	for (int i = mSnakeChain.size() - 1; i >= 0; i--){
		mSnakeChain[i].bodyTexture->render(mSnakeChain[i].x, mSnakeChain[i].y);
	}
}