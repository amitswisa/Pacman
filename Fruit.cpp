#include "Fruit.h"

#include <random>
#include <sstream>

void Fruit::initFruit(Board* board, vector<Ghost>& ghosts, Pacman& pacman, Position& legend, Mode& mode) {

	// fruit appear
	if (!this->isActive) {

		// do in case not load mode.
		if (mode.getMode() != LOAD_MODE)
		{
			// check if fruit "to appear" timer is 0.
			if (this->waitToAppearTime <= 0) {
				this->isActive = true;

				this->pos = getRandomPosition(board, ghosts, pacman, legend);
				this->fruitPoint = (rand() % 5) + 5;

				// print fruit appearing format to file.
				if (mode.getMode() == SAVE_MODE) {
					string temp = FRUIT_FILE;
					temp += " AP ";
					temp.append(to_string(this->pos.getXPosition()) + " ");
					temp.append(to_string(this->pos.getYPosition()));
					mode.doSteps(temp, fruitPoint + '0');
				}

				this->setNewWaitingTime();
				this->printCreature();
			}
		}
		else
		{
			// check if next move is fruit move.
			if (mode.getStepsFile().peek() == 'F')
			{
				// set values as written in file - load mode.
				string temp;
				getline(mode.getStepsFile(), temp);
				if (temp.find("AP") != string::npos)
				{
					this->isActive = true;

					temp = temp.substr(5, temp.length());
					stringstream ss(temp);
					int x, y;
					ss >> x; // get x
					ss >> y; // get y
					this->pos.setPosition(x,y);
					ss >> this->fruitPoint; // get fruit points.
					this->printCreature();
				}
				else
					mode.wrongFiles(); // stop game if steps file format is wrong.
			}
		}
	}

	if(this->isActive) {
		// if there are no ghost at all so move with the speed of pacman movment.
		// else if there are ghosts, move 1:2 as pacman move.
		if (ghosts.size() == 0 || (ghosts.size() > 0 && ghosts[0].getSpeedVSPackman() == 0)) {
			
			if (mode.getMode() != LOAD_MODE) {
				// check if "disappear" timer of fruit is 0.
				if (this->waitToAppearTime <= 0)
				{
					this->isActive = false;

					// Save fruit disappear log in file.
					if (mode.getMode() == SAVE_MODE)
					{
						string temp = FRUIT_FILE;
						temp += " DIS";
						mode.doSteps(temp);
					}

					this->setNewWaitingTime();
				}
			}

			// random/load next fruit move & make fruit disappear if timer is 0 or loaded from file.
			this->moveRandomly(board, mode);
		}
	}

}

void Fruit::setNewWaitingTime() {
	this->waitToAppearTime = (rand() % (20)) + 10; // generate timer for fruit to be appear/disappear.
}

void Fruit::printCreature() {
	gotoxy(this->pos.getYPosition(), this->pos.getXPosition());
	cout << this->fruitPoint;
}

void Fruit::decreaseTimer() {
	this->waitToAppearTime--;
}

Position Fruit::getRandomPosition(Board* board, vector<Ghost>& ghosts, Pacman& pacman, Position& legend) {

	int x, y;

	bool noFoundPos;

	/*
	*  keep re-generate random movment if fruit random pos generated is:
	*		1. position is a wall.
	*		2. position is in same position as pacman.
	*		3. position is in legend.
	*		4. position is the same as one of the ghosts.
	*/

	 do{
		noFoundPos = false;

		x = (rand() % board->getColSize());
		y = (rand() % board->getRowSize());

		if (board->getCellObject(x, y) == WALL)
			noFoundPos = true;

		if (pacman.getPosition().getXPosition() == x && pacman.getPosition().getYPosition() == y)
			noFoundPos = true;

		if(x >= legend.getXPosition() && x <= legend.getXPosition()+2 
			&& y >= legend.getYPosition() && y <= legend.getYPosition()+19)
			noFoundPos = true;

		for (auto& ghost : ghosts) {
			if (ghost.getPosition().getXPosition() == x && ghost.getPosition().getYPosition() == y)
				noFoundPos = true;
		}

	 } while (noFoundPos);


	 return Position(x,y);
}

void Fruit::moveRandomly(Board* board, Mode& mode) {

	Position newPos = this->pos;
	if (mode.getMode() != LOAD_MODE) {
		do {
			newPos = this->pos;

			int dir = (rand() % (4)) + 1;

			switch (dir)
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

		} while (board->isOutBorder(newPos) == TRUE
			|| board->getCellObject(newPos.getXPosition(), newPos.getYPosition()) == WALL);

	}
	
	// if fruit is active and were on load mode.
	if (mode.getMode() == LOAD_MODE && this->isActive) {
		
		// get fruit next move (move or disappear).
		newPos = mode.getFruitMove(this->pos);
		
		// check if next move is fruit disappear.
		if (newPos.getXPosition() == NOT_FOUND)
			this->isActive = false;
	}

	this->resumePrevObj(board);
	 
	if (this->isActive) {

		// if were in save mode.
		if (mode.getMode() == SAVE_MODE)
			mode.doSteps(FRUIT_FILE, this->getDirFromPos(newPos));

		this->pos = newPos;
		this->printCreature();
	}

}

void Fruit::fruitCollision(bool isGhost, Mode& mode) {
	this->isActive = false;

	if (mode.getMode() != LOAD_MODE)
		this->setNewWaitingTime();

	if (!isGhost)
		this->scoreAchieved += this->fruitPoint;
}

bool Fruit::active() {
	return this->isActive;
}

int Fruit::getBonusScore() {
	return this->scoreAchieved;
}