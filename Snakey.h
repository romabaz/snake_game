#pragma once
#include<vector>
#include<queue>
#include "GameObject.h"
class Snakey :	public GameObject {
private:
	/*
	Each indivisible element of Snakey is called Quantum.
	Snakey grows by Quantums. One food - one more quantum at minimum.
	TODO: read about inner classes scopes in cpp
	*/
	class SnakeyQuantum {
	public:
		SnakeyQuantum() {
			x = 0;
			y = 0;
			direction = NONE;
		}

		SnakeyQuantum(int x, int y, Direction dir) {
			this->x = x;
			this->y = y;
			this->direction = dir;
			this->nextEventId = 0;
		}

		~SnakeyQuantum() {}

		int x;
		int y;
		Direction direction;
		std::size_t nextEventId;
	};

	struct SnakeyEvent {
		GameEvent event;
		int x;
		int y;
		inline SnakeyEvent(int x, int y, GameEvent gameEvent) {
			this->x = x;
			this->y = y;
			this->event = gameEvent;
		}
	};

	//an array of quantums constitutes a snakey body
	std::vector<SnakeyQuantum*> mSnakeyBody;
	//a vector of game events, containing the place where it has happenned with the event itself
	std::vector<SnakeyEvent*> mSnakeyEventVec;
	//keep current length of Snakey (number of quantums including head)
	std::size_t mSnakeyLength = 0;
	//snakey speed
	short mSpeed = 0;

	void applyGameEvent(SnakeyQuantum* sq, GameEvent gEvent);
	void move(SnakeyQuantum* sq);
	std::size_t findNextEventId(std::size_t eventId);

public:
	Snakey();
	~Snakey();
	
	void init(int x, int y, Direction dir) override;
	void tick(GameEvent gEvent) override;
	void tick() override;
	void draw();
	

};

