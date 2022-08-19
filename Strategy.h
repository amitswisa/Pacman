#ifndef _STRATEGY
#define _STRATEGY

#include "Utils.h"
#include "Mode.h"

class Ghost;
class Board;
class Position;

class Strategy
{

	public:
		Strategy() {};

		virtual ~Strategy() {}

		virtual Position move(Board* board, Ghost* ghost, Position& pacmanPos, vector<Ghost>& ghosts) = 0;
		int getRandomPosition(Position& newPos, int direction);
		bool isValid(Board* board, Position& pos);
		virtual void fixPathArray(Board& board, Position& pacmanPos, vector<Ghost>& ghosts) {};
		virtual void setBFSarray(int _rowSize, int _colSize) {};
		virtual int** getPathToPacmanArray() { return NULL; };

		bool isPositionOnGhosts(Position& newPos, Ghost* curGhost, vector<Ghost>& ghosts);
};


#endif