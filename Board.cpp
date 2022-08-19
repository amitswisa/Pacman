#include "Board.h"

Board::Board() : rowSize(0), colSize(0) {};

void Board::initStage(const string& stageName) {

	//Reading stage drawing from a file, clear screen and go to 0,0
	this->rowSize = 0;
	this->colSize = 0;
	system("cls");
	gotoxy(0, 0);
	board.clear();

	ifstream boardGame(stageName);

	if (!boardGame) {
		cout << "Error, file couldn't be opened" << endl;
		exit(1);
	}

	string line;

	int legendx = NOT_FOUND, legendy = NOT_FOUND;

	//handle first row
	if (this->rowSize == 0) {
		getline(boardGame, line);
		this->rowSize = line.length(); // update each row size.
		int findUppercent = line.find("&");
		if (findUppercent != string::npos)
		{
			// save legend location
			legendx = 0;
			legendy = findUppercent;

			if (this->rowSize - 1 - findUppercent < 20)
			{
				for (int i = this->rowSize - findUppercent;i < 20;i++)
					line += '%';

				this->rowSize += 20 - (this->rowSize - findUppercent);
			}
		}

		board.push_back(line);
		this->colSize++;
	}

	// Read all rows except first row.
	while (getline(boardGame, line))
	{
		string temp;
		int lineLength = line.length();

		temp = line.substr(0, this->rowSize);
		for (int i = lineLength; i < this->rowSize;i++) {
			temp += ' ';
		}

		// try to find '&' in each line.
		int tempFind = temp.find("&");
		if (tempFind != string::npos)
		{
			
			// check validation of legend position.
			if (this->rowSize - tempFind < 20)
				throw "ERROR: Legend position is forbidden.";

			// save legend location
			legendx = this->colSize;
			legendy = tempFind;
		}

		board.push_back(temp);
		this->colSize++;
	}

	// fix game table size because of '&' if needed.
	if (legendx >= this->colSize - 2 && legendx <= this->colSize - 1)
	{
		int rowsToAdd = 3 - (this->colSize - legendx);
		for (int i = 0;i < rowsToAdd;i++) {
			string str = "";
			for (int j = 0;j < this->rowSize;j++) {
				str += ' ';
			}
			board.push_back(str);
			this->colSize++;
		}
	}

	boardGame.close();
}

void Board::printAndUpdateBoard(Pacman& pacman,vector<Ghost>& ghostArr, Position& legendPos, int& stageTotalScore) {

	// board size valid
	if (this->getRowSize() > 80 || this->getColSize() > 25)
		throw "ERROR: This screen size is forbidden.";

	// Printing pacman board
	for (int i = 0;i < board.size();i++) {
		for (int j = 0;j < board[i].length();j++) {
			switch (board[i][j]) {
				case EMPTY_CELL: {
					cout << BREADCRUMBS;
					board[i][j] = BREADCRUMBS;
					stageTotalScore++;
					break;
				}
				case '%': {
					board[i][j] = EMPTY_CELL;
					cout << EMPTY_CELL;
					break;
				}
				case WALL: {
					cout << WALL;
					break;
				}
				case PACMAN: {

					// check if pacman already initillized and if so, there is more then 1 pacman.
					if (pacman.getPosition().getXPosition() != NOT_FOUND)
						throw "ERROR: There is more then one pacman in screen.";

					pacman.setStartPosition(Position(i,j));
					board[i][j] = EMPTY_CELL;
					cout << PACMAN;
					break;
				}
				case GHOST: {

					// create and insert new ghost.
					Ghost newGhost(Position(i,j));
					ghostArr.push_back(newGhost);

					// validation of ghosts amount
					if (ghostArr.size() > 4)
						throw "ERROR: There are more then 4 ghosts in your screen.";

					board[i][j] = BREADCRUMBS; // set breadcrumb underneath ghost. 
					cout << GHOST;
					stageTotalScore++;
					break;
				}
				case LEGEND: {

					if (legendPos.getXPosition() != NOT_FOUND && legendPos.getYPosition() != NOT_FOUND)
						throw "There is more then 1 legend in screen.";

					legendPos.setPosition(i, j);
					cout << EMPTY_CELL;
					stageTotalScore++;
					break;
				}
			}
		}
		cout << endl;
	}

	// there is no pacman in file.
	if (pacman.getPosition().getXPosition() == NOT_FOUND)
		throw "Pacman was not found in file.";

	// there is no legend in file.
	if (legendPos.getXPosition() == NOT_FOUND)
		throw "Legend was not found in file.";

	// handle legend rewrite
	for (int i = legendPos.getXPosition();i < legendPos.getXPosition()+3;i++) {
		for (int j = legendPos.getYPosition();j < legendPos.getYPosition() + 20;j++) {

			// if legend cell value is other then '%' at first.
			if (board[i][j] != EMPTY_CELL && board[i][j] != WALL)
				stageTotalScore -= 1;

			board[i][j] = EMPTY_CELL;
			gotoxy(j,i);
			cout << EMPTY_CELL;
		}
	}
}

char Board::getCellObject(int x, int y) {
	return this->board[x][y];
}

void Board::setCellObject(int x, int y, char obj) {
	this->board[x][y] = obj;
}

bool Board::isOutBorder(Position& position) {

	int x = position.getXPosition();
	int y = position.getYPosition();

	if (x <= -1 || y <= -1 || y >= this->rowSize || x >= this->colSize)
		return true;

	return false;

}

// Checks if tunnel is approved and return new point if so.
// also returns new position with x=-200&y=-200 if not valid tunnel.
Position Board::tunnelPosition(Position& position) const {

	if (position.getYPosition() <= -1)
		return Position(position.getXPosition(), -1 + rowSize);
	else if(position.getYPosition() >= rowSize)
		return Position(position.getXPosition(), 0);

	if (position.getXPosition() <= -1)
		return Position(-1 + colSize, position.getYPosition());
	else if(position.getXPosition() >= colSize)
		return Position(0, position.getYPosition());
	
	return Position(-200,-200);
}

int Board::getRowSize() {
	return this->rowSize;
}

int Board::getColSize() {
	return this->colSize;
}