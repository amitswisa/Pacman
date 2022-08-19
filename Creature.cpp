#include "Creature.h"

#include "Board.h"

Position& Creature::getPosition() {
	return this->pos;
}

void Creature::setDirection(char dir) {
	this->direction = dir;
}

char Creature::getDirection() {
	return this->direction;
}

void Creature::setStartPosition(Position pos) {
	this->startPosition = pos;
}

void Creature::goToStartPosition() {
	this->pos = this->startPosition;
}

void Creature::resumePrevObj(Board* board) {
	// return the previouse object that been displayed before ghost.
	gotoxy(this->pos.getYPosition(), this->pos.getXPosition());
	cout << board->getCellObject(this->pos.getXPosition(), this->pos.getYPosition());
}

char Creature::getDirFromPos(Position& newPos) {

	int x, y; //x=row, y=col
	x = newPos.getXPosition() - this->pos.getXPosition();
	y = newPos.getYPosition() - this->pos.getYPosition();

	if (x != y) // != (0,0)
	{
		if (x == 0)
		{
			if (y == 1)
				return RIGHT;
			
			if (y == -1)
				return LEFT;
		}

		if (y == 0)
		{
			if (x == -1)
				return UP;

			if (x == 1)
				return DOWN;
		}
	}

	return STAY;

}
