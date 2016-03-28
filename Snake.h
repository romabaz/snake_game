#include"GameTexture.h"
#include<vector>
#include<queue>

typedef enum Directions{
	LEFT,
	RIGHT,
	UP,
	DOWN
} Directions;

typedef struct TurnEvent{
	int x;
	int y;
	Directions dir;
} TurnEvent;

typedef struct Chain{
	SDL_Rect* bodyRect;
	int x;
	int y;
	Directions dir;
	std::queue<TurnEvent*> pathHistory;
} Chain;


class Snake
{
public:
	Snake(GameTexture* snakeTexture, int x, int y);
	~Snake();

	//Returns total snake length including head
	int addBodyChain();
	void move();

	bool setDirection(Directions newDirection);
	void setSpeed(short newSpeed);
	short getSpeed();

	//Renders full snake
	void render();

private:
	int mSnakeLenght;
	short mSpeed;
	short mChainRadius;
	double mHeadAngle;
	
	//sprite size (x=y=80)
	int mSpriteStepPx = 80;

	GameTexture* mSnakeTexture;
	SDL_Rect mSpriteClips[12];
	std::vector<Chain> mSnakeChain;
	

	//Check collision for the next frame
	bool isCollide();

	void moveDirection(Chain& itemChain);
	void changeChainDirection(Chain& bodyChain, TurnEvent* nextTurnState, int chainNumber, Chain& nextChain);

	TurnEvent* readNextTurnState(Chain& bodyItem);

	void initSpriteClips();

};