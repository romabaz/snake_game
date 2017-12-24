#pragma once
#include<vector>
#include<deque>
#include "GameWorld.h"
class Snakey : public GameObject {
private:
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
			iam = SNAKEY_QUANTUM1;
		}
		SnakeyQuantum(GameObjectType type): iam(type) {
			x = 0;
			y = 0;
			direction = NONE;
		}

		SnakeyQuantum(int x, int y, Direction dir) {
			this->x = x;
			this->y = y;
			this->direction = dir;
			nextSnakeyEventId = -1;
		}

		~SnakeyQuantum() {}

		int x;
		int y;
		Direction direction;
		std::size_t nextSnakeyEventId;
		GameObjectType iam;
	};

	GameObjectType iam = SNAKEY;
	//an array of quantums constitutes a snakey body
	std::vector<SnakeyQuantum*> mSnakeyBody;
	//a vector of game events, containing the place where it has happenned with the event itself
	std::deque<SnakeyEvent*> mSnakeyEvents;
	//keep current length of Snakey (number of quantums including head)
	std::size_t mSnakeyLength = 0;
	//snakey speed
	short mSpeed = 0;

	void applyGameEvent(SnakeyQuantum* sq, GameEvent gEvent);
	void move(SnakeyQuantum* sq);

public:
	Snakey();
	~Snakey();

	void init(int x, int y, Direction dir) override;
	void tick(GameEvent gEvent) override;
	void draw();


};

