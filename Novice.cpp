#include "Novice.h"

Position Novice::move(Board* board, Ghost* ghost, Position& pacmanPos, vector<Ghost>& ghosts) {
	
	Position newPos;

	// Randomize new position for ghost each iteration and check collision with walls.
	bool firstIter = true;
	do {
		newPos = ghost->pos;

		if (!firstIter || ghost->stepsNum == 0)
			ghost->direction = NOT_FOUND;

		ghost->direction = this->getRandomPosition(newPos, ghost->direction);
		
		firstIter = false;

		// check other ghosts positions and avoid moving there.
	} while (!isValid(board, newPos));

	ghost->stepsNum++; // increase ghost steps by 1.
	
	ghost->stepsNum = ghost->stepsNum % 20; // reset ghost steps when getting 20 moves.

	return newPos;
}