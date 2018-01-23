#pragma once
#include<deque>
#include "GameObject.h"
class Snakey : public GameObject {
private:
	struct SnakeyEvent {
		GameEvent event;
		int x;
		int y;
		std::size_t nextQuantumId;
		SnakeyEvent(int xVal, int yVal, GameEvent gameEvent) : x(xVal), y(yVal), event(gameEvent), nextQuantumId(1) {
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

	void applyGameEvent(SnakeyQuantum* sq, GameEvent gEvent);
	void move(SnakeyQuantum* sq);
	void checkQueuedEventToHappen(SnakeyQuantum* sq, std::size_t quantumId);
	std::vector<GamePoint> getSnakeyFrontLine();

public:
	Snakey();
	~Snakey();

	void init(int x, int y) override;
	void applyGameEvent(const GameEvent gEvent) override;
	void move() override;
	std::vector<DrawConstruct> getDrawConstruct() const override;
	inline const GameObjectType getType() const override { return iam; }
	bool doesHeadHit(std::vector<GamePoint> points);
	void grow();
	
};

