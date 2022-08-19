#ifndef _BOARD_
#define _BOARD_

#include "Utils.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Screen.h"

class Pacman;
class Ghost;
class Strategy;

class Board {

	private:
		vector<string> board;
		int rowSize, colSize;

	public:
		//Constructor
		Board();

		~Board() {
			board.clear();
		}

	public:
		void initStage(const string& stageName);
		void printAndUpdateBoard(Pacman& pacman, vector<Ghost>& ghostArr, Position& legendPos, int& stageTotalScore);
		char getCellObject(int x, int y);
		void setCellObject(int x, int y, char obj);
		bool isOutBorder(Position& position);
		Position tunnelPosition(Position& position) const;
		int getRowSize();
		int getColSize();
};


#endif