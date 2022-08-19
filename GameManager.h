#ifndef  GAME_MANAGER
#define GAME_MANAGER

#include "Mode.h"
#include "Game.h"
#include "Novice.h"
#include "Best.h"

class GameManager {

private:
	Game* pacman;
	Screen pacman_files;

public:
	GameManager() { this->pacman = NULL; };

public:
	void displayMenu(Mode& mode);
	void printInstructions();
	void exitGame();
	void runPacman(Mode& mode);
	Strategy* chooseStrategy();

};

#endif 
