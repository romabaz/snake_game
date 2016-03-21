#include"GameTexture.h"
#include<vector>

typedef enum Directions{
	LEFT,
	RIGHT,
	UP,
	DOWN
} Directions;

typedef struct Chain{
	GameTexture* bodyTexture;
	int x;
	int y;
	Directions dir;
	int xApplyDir = -1;
	int yApplyDir = -1;
	Directions newDir;
} Chain;

class Snake
{
public:
	Snake(GameTexture* headTexture, int x, int y);
	~Snake();

	//Returns total snake length including head
	int addBodyChain(GameTexture* bodyTexture);
	//Returns new head coordinates
	SDL_Point move();
	SDL_Point moveLeft();
	SDL_Point moveRight();
	SDL_Point moveUp();
	SDL_Point moveDown();

	bool setDirection(Directions newDirection);
	void setSpeed(short newSpeed);
	short getSpeed();

	//Renders full snake
	void render();

private:
	int mSnakeLenght;
	short mSpeed;
	short mChainRadius;
	//array of headTextures
	std::vector<Chain> mSnakeChain;

	//Check collision for the next frame
	bool isCollide();


};