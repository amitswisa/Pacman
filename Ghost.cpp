#include <typeinfo>

#include "Ghost.h"
#include "Board.h"
#include "Novice.h"

void Ghost::printCreature() {
	// Print ghost according to its coordinates.
	gotoxy(this->pos.getYPosition(), this->pos.getXPosition());
	cout << GHOST;
}

void Ghost::move(Board* board, Position& pacmanPos ,vector<Ghost>& ghosts, Mode& mode, int index) {
	// slower ghost movment by 1/speedVsPacman.
	if (this->speedVsPacman == 0) {

		Position newPos;

		// if were in save mode.
		if (mode.getMode() != LOAD_MODE) {
			newPos = this->strategy->move(board, this, pacmanPos, ghosts);
			// Create "G0/G1/G2/G3" for file.
			if (mode.getMode() == SAVE_MODE) {
				string ghostName = GHOST_FILE;
				ghostName += (index + '0');
				mode.doSteps(ghostName, this->getDirFromPos(newPos));
			}
		}
		else
			newPos = mode.getGhostMove(this->pos); //load mode

		this->resumePrevObj(board);
		this->pos = newPos; // updating ghost coordinates.
		this->printCreature();
	}

	if (this->speedVsPacman == 1)
		this->speedVsPacman = 0;
	else
		this->speedVsPacman = 1;
}

void Ghost::setStrategy(Strategy* _strategy) {
	this->strategy = _strategy;
}

int Ghost::getSpeedVSPackman() {
	return this->speedVsPacman;
}