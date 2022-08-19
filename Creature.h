#ifndef _CREATURE
#define _CREATURE

#include "Utils.h"
#include "Mode.h"

class Board;

class Creature {

	protected:
		Position pos;
		Position startPosition;
		char direction;

		Creature() {
			this->direction = NOT_FOUND;
		};

	public:
		virtual ~Creature() {};
		
		// Abstract functions.
		virtual void printCreature() = 0;

		// shared functions
		Position& getPosition();
		void setDirection(char dir);
		char getDirection();
		void setStartPosition(Position pos);
		void goToStartPosition();
		void resumePrevObj(Board* board);
		char getDirFromPos(Position& newPos);
};

#endif