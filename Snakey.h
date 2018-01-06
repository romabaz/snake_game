#pragma once
#include<deque>
#include "GameObject.h"
class Snakey : public GameObject {
private:
	struct SnakeyEvent {
		GameEvent event;
		int x;
		int y;
		SnakeyEvent(int xVal, int yVal, GameEvent gameEvent) : x(xVal), y(yVal), event(gameEvent) {
		}
	};
	/*
	Each indivisible element of Snakey is called Quantum.
	Snakey grows by Quantums. One food - one more quantum at minimum.
	TODO: read about inner classes scopes in cpp
	*/
	class SnakeyQuantum {
	public:
		SnakeyQuantum() : x(0), y(0), direction(NONE), iam(SNAKEY_QUANTUM1) {
		}

		SnakeyQuantum(GameObjectType type): x(0), y(0), direction(NONE), iam(type) {
		}

		SnakeyQuantum(int x, int y, Direction dir, GameObjectType type): x(x), y(y), direction(dir), iam(type) {
		}

		~SnakeyQuantum() {}

		int x;
		int y;
		Direction direction;
		std::size_t nextSnakeyEventId;
		const GameObjectType iam;
	};

	const GameObjectType iam = SNAKEY;
	//an array of quantums constitutes a snakey body
	std::vector<SnakeyQuantum*> mSnakeyBody;
	//a vector of game events, containing the place where it has happenned with the event itself
	std::deque<SnakeyEvent*> mSnakeyEvents;
	//keep current length of Snakey (number of quantums including head)
	std::size_t mSnakeyLength;
	short mSpeed;
	//drawing construct used by GameWorld to render
	std::vector<DrawConstruct> drawConstruct;

	void applyGameEvent(SnakeyQuantum* sq, GameEvent gEvent);
	void move(SnakeyQuantum* sq);

public:
	Snakey();
	~Snakey();

	void init();
	void tick(GameEvent gEvent) override;
	inline std::vector<DrawConstruct> getDrawConstruct() const override { return drawConstruct; }
	inline const GameObjectType getType() const override { return iam; }

	void grow();
	
};

