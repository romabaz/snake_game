#include "Snakey.h"



Snakey::Snakey()
{
	//set initial capacity
	mSnakeyBody.reserve(8);
	mSnakeyBody.push_back(new SnakeyQuantum(0, 0, Directions::NONE));
}


Snakey::~Snakey()
{
}
