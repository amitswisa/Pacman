#ifndef _GHOSTS
#define _GHOSTS

#include <random>
#include "Creature.h"
#include "Strategy.h"

class Board;

class Ghost:public Creature {

private:
	Strategy* strategy;
	int speedVsPacman; // Speed of ghost in compare to pacman speed (1:n).
	int stepsNum;

	// strategy class premission.
	friend class Novice;
	friend class Best;
	friend class Good;


public:
	Ghost():speedVsPacman(1), stepsNum(0) {};
	Ghost(Position _pos, int _speedVsPacman = 1) : speedVsPacman(_speedVsPacman), stepsNum(0) {
		this->pos = _pos;
		this->startPosition = _pos;
	};
	
public:
	virtual void printCreature();
	void move(Board* board, Position& pacmanPos, vector<Ghost>& ghosts, Mode& mode, int index);
	void setStrategy(Strategy* _strategy);
	int getSpeedVSPackman();
};

#endif