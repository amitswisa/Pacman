#ifndef _THE_PACMAN
#define _THE_PACMAN

#include "Creature.h"
#include "Board.h"
#include "Mode.h"

class Board;
class Ghost;

class Pacman:public Creature 
{

	public:
		// Constructor
		Pacman() {
			this->direction = 1;
		};

		// Operator override
		bool operator&(Position& ghostPos) {
			if (this->getPosition().getXPosition() == ghostPos.getXPosition()
				&& this->getPosition().getYPosition() == ghostPos.getYPosition())
				return TRUE;

			return FALSE;
		};


		// Functions
		virtual void printCreature();
		void move(char* key, Board* board, Mode& mode);
		void setStartPosition(Position pos);
};
#endif