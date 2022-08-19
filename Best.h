#ifndef _BEST
#define _BEST

#include "Strategy.h"

#include "Ghost.h"
#include "Board.h"

class Best : virtual public Strategy {

private:
	int** pathToPacman;
	bool** isVisited;
	int rowSize, colSize;

	int dx[4] = { 0, 1, 0, -1 };
	int dy[4] = { 1, 0, -1, 0 };

public:
	Best() : pathToPacman(NULL), isVisited(NULL) {};

	virtual ~Best() {
		for (int i = 0;i < this->rowSize;i++) {
			delete[] isVisited[i];
			delete[] pathToPacman[i];
		}
		delete[] isVisited;
		delete[] pathToPacman;
	}

	virtual Position move(Board* board, Ghost* ghost, Position& pacmanPos, vector<Ghost>& ghosts) override;
	virtual void fixPathArray(Board& board, Position& pacmanPos, vector<Ghost>& ghosts);
	virtual void setBFSarray(int _rowSize, int _colSize);
};
#endif