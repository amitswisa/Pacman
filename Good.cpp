#include "Good.h"

Position Good::move(Board* board, Ghost* ghost, Position& pacmanPos, vector<Ghost>& ghosts) {

	Position toReturn;
	static int ghostTurn = 0;


	if (this->isBest)
	{
		toReturn = Best::move(board, ghost, pacmanPos, ghosts);
		ghost->stepsNum++; // increase ghost move counter.

		if (ghost->stepsNum % 20 == 0) {
			ghost->stepsNum = 0;
			if(ghostTurn == ghosts.size()-1)
				this->isBest = false;
		}
	}
	else {
		ghost->setDirection(NOT_FOUND);
		toReturn = Novice::move(board, ghost, pacmanPos, ghosts);

		if (ghost->stepsNum % 5 == 0) {
			ghost->stepsNum = 0;
			if (ghostTurn == ghosts.size() - 1)
				this->isBest = true;
		}
	}

	ghostTurn++;
	ghostTurn %= ghosts.size();

	return toReturn;

}