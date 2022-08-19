#ifndef _GOODLEVEL
#define _GOODLEVEL

#include "Best.h"
#include "Novice.h"

class Best;
class Novice;

class Good : public Best, public Novice {

	private:
		bool isBest;

public:
	Good() :isBest(true) {};

	virtual ~Good() {};

	virtual Position move(Board* board, Ghost* ghost, Position& pacmanPos, vector<Ghost>& ghosts) override;

};
#endif