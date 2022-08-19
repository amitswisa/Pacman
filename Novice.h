#ifndef NOVICE
#define NOVICE

#include "Strategy.h"

#include "Ghost.h"
#include "Board.h"
#include "Fruit.h"

class Novice : virtual public Strategy
{
public:

	Novice() {};

	virtual Position move(Board* board, Ghost* ghost, Position& pacmanPos, vector<Ghost>& ghosts) override;

};

#endif