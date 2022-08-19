#include "Strategy.h"

#include "Board.h"

int Strategy::getRandomPosition(Position& newPos, int direction) {

	if (direction == NOT_FOUND) {
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(1, 4); // define the range
		direction = distr(gen);

		if (newPos.getXPosition() == 2 && newPos.getYPosition() == 2)
			cout << direction << endl;

	}

	switch (direction)
	{
	case GLEFT:
		newPos.goLeft();
		break;
	case GRIGHT:
		newPos.goRight();
		break;
	case GUP:
		newPos.goUp();
		break;
	case GDOWN:
		newPos.goDown();
		break;
	}

	return direction;
}

bool Strategy::isValid(Board* board, Position& pos)
{
	return (board->isOutBorder(pos) == FALSE
		&& board->getCellObject(pos.getXPosition(), pos.getYPosition()) != WALL);
}

bool Strategy::isPositionOnGhosts(Position& newPos, Ghost* curGhost, vector<Ghost>& ghosts) {
	
	for (auto& gh : ghosts) {
		if (&gh != curGhost && gh.getPosition() == newPos)
			return true;
	}

	return false;

}