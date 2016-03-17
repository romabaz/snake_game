#include"GameTexture.h"
#include<vector>

typedef enum Directions{
	LEFT,
	RIGHT,
	UP,
	DOWN
} Directions;

struct Chain{
	GameTexture* bodyTexture;
	int x;
	int y;
};

class Snake
{
public:
	Snake(int startX, int startY, Chain headChain) : mSnakeChain(5){};
	~Snake();

	//Returns total snake length including head
	int addBodyChain(Chain bodyChain);
	//Returns new head coordinates
	SDL_Point move(Directions dir);
	SDL_Point moveLeft();
	SDL_Point moveRight();
	SDL_Point moveUp();
	SDL_Point moveDown();

	//Returns current head coordinates
	SDL_Point getCurrentHead();

	//Renders full snake

	void render();

private:
	int mXHead;
	int mYHead;
	int mSnakeLenght;

	//array of headTextures
	std::vector<Chain> mSnakeChain;


};