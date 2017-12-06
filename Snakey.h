#pragma once
#include<vector>
#include "GameObject.h"
class Snakey :	public GameObject {
public:
	Snakey();
	~Snakey();

private:
	/*
	Each indivisible element of Snakey is called Quantum. 
	Snakey grows by Quantums. One food - one more quantum at minimum.
	*/
	class SnakeyQuantum {
	private:
		int x;
		int y;
		Direction direction;

	public:
		SnakeyQuantum() {
			x = 0;
			y = 0;
			direction = Directions::NONE;
		}

		SnakeyQuantum(int x, int y, Direction dir) {
			this->x = x;
			this->y = y;
			this->direction = dir;
		}

		~SnakeyQuantum() {}

	};

	//an array of quantums constitutes a snakey body
	std::vector<SnakeyQuantum*> mSnakeyBody;
};

