#include "Pacman.h"

void Pacman::printCreature() {
	gotoxy(this->pos.getYPosition(), this->pos.getXPosition());
	cout << PACMAN;
}

void Pacman::setStartPosition(Position _pos) {
	this->startPosition = _pos;
	this->pos = _pos;
}

void Pacman::move(char* key, Board* board, Mode& mode) {

	if (*key == DEFAULT)
		return;

	*key = tolower(*key); // Allow big and small letters.

	// Keep moving to same last direction when pressing unrelevant keys.
	if (*key != LEFT && *key != RIGHT && *key != UP
		&& *key != DOWN && *key != STAY)
		*key = this->direction;
	else
		this->direction = *key;

	if (mode.getMode() == SAVE_MODE && *key != DEFAULT) 
		mode.doSteps(PACMAN_FILE, *key);

	Position newPos = this->pos;

	//Updating new coordinates according to player's move choice.
	switch (*key)
	{
	case LEFT:
		newPos.goLeft();
		break;

	case RIGHT:
		newPos.goRight();
		break;

	case UP:
		newPos.goUp();
		break;

	case DOWN:
		newPos.goDown();
		break;

	default: //STAY
		return;
		break;
	}
	
	// If pacman is at the border of the board check if tunnel approved.
	if (board->isOutBorder(newPos)) {
		Position npos = board->tunnelPosition(newPos);
		if (npos.getXPosition() != NOTUNNEL)
			newPos = npos;
	}

	// Check if the new position of pacman is not a wall.
	char cellChar = board->getCellObject(newPos.getXPosition(), newPos.getYPosition());

	if (cellChar != WALL)
	{
		gotoxy(pos.getYPosition(), pos.getXPosition());
		cout << " ";

		this->pos = newPos;
		printCreature();
	}

}