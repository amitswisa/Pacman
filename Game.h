#ifndef _GAME
#define _GAME

#include <cstdlib>

#include "Mode.h"
#include "Pacman.h"
#include "Strategy.h"
#include "Board.h"
#include "Screen.h"
#include "Fruit.h"
#include "Good.h"

class Game {

private:
	int playerScore;
	int stageTotalScore; // number of breadcrumbs (food) in stage files
	int lifePoints;
	bool gamePause;
	Position legend;
	Screen screens;
	Board board;
	Pacman player;
	vector<Ghost> ghosts;
	Fruit fruit;

public:
	Game(const Screen& _screens)
	{
		this->lifePoints = 3;
		this->playerScore = 0;
		this->stageTotalScore = 0;
		this->gamePause = FALSE;
		this->screens = _screens;

		system("cls");	//clear screen
	};

	~Game() {
		ghosts.clear();
	}

public:
	void initGame(Strategy* strategy, Mode& mode);
	void pauseGame(char KEY);
	void printScoreAndLife(bool collision);
	bool isPlayerWon();
	bool isGameOver();
	bool checkCollision(Mode& mode, int timer);
	void resumeCharactersToStart();
	void setGhostsStrategy(Strategy* strategy);
	Screen& getScreens();
};

#endif