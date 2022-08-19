#include "Game.h"

#include <cstdlib>

void Game::initGame(Strategy* strategy, Mode& mode) {

	// Play all screens in specified directory.
	bool loadModeSucced = false;
	for (int i = 0; i < screens.pacman_screens.size() && !this->isGameOver(); i++) {

		int timer = 0; //count point of time

		// try&catch board and creatures errors if there are any.
		try {
			// init steps and results file to save or load mode.
			mode.initFiles(screens.pacman_screens[i]);

			// initillize relevant stage, load screen etc....
			this->board.initStage(screens.pacman_screens[i]);

			// clean ghosts vector, reset pacman direction and position.
			ghosts.clear();
			player.setDirection(DEFAULT);
			player.setStartPosition(Position(NOT_FOUND, NOT_FOUND));
			legend.setPosition(NOT_FOUND, NOT_FOUND);

			// Print pacman board and update positions and stage array.
			this->board.printAndUpdateBoard(player, ghosts, legend, this->stageTotalScore);
		}
		catch (const char* msg) {

			system("cls");

			// if im in load mode and dont exist steps&result file for current screen.
			if (strcmp(msg, "next stage") != 0)
			{
				cout << msg;
				cout << endl << "Press any key to continue...";
				_getch();
			}
			continue;
		}

		loadModeSucced = true; // if load mode worked at lease once.
		setGhostsStrategy(strategy); // change Ghosts strategy.

		char pressedKey = DEFAULT; // 1 is default value to help game pause until player presses relevant key.
		bool collision = FALSE; // flag of collision between pacman and ghosts.

		do {

			hideCursor();
			printScoreAndLife(collision);

			// if player is on the same square as ghost.
			if (collision) {
				resumeCharactersToStart();
				pressedKey = DEFAULT;
				player.setDirection(pressedKey);
				collision = FALSE;
			}
			
			if (mode.getMode() != LOAD_MODE) {
				if (_kbhit()) {
					pressedKey = _getch();	// read pressed key.
					this->pauseGame(pressedKey);	// Pausing and resuming when pressing ESC.
				}
			}
			else // load_mode
				pressedKey = mode.getPacmanMove();

			// if game is not paused && 
			if (!this->gamePause && pressedKey != DEFAULT) {

				this->player.move(&pressedKey, &this->board, mode);
				timer++; // increase time of pointasdasd
	
				collision = checkCollision(mode, timer);

				// if pacman ate all breadcrumbs
				if (this->isPlayerWon())
					continue;
					
				if (!collision)
				{
					// use BFS on pacman in Best and Good mode.
					// on Novice mode, fixPathArray function is empty therefor not doing anything.
					if(ghosts.size() > 0 && strategy != NULL)
						strategy->fixPathArray(board, player.getPosition(), ghosts);

					// Fruit handle
					fruit.initFruit(&board, ghosts, player, legend, mode);
					collision = checkCollision(mode, timer);

					// ghost movment
					for (int i = 0; i < ghosts.size() && !collision; i++) {
						ghosts[i].move(&board, player.getPosition(), ghosts, mode, i);
						collision = checkCollision(mode, timer);
					}

				}

				fruit.decreaseTimer(); // update fruit timer

				// show game proccess when not load mode with silent true.
				if (!mode.getSilentStatus()) {

					// Slow down game pace.
					if (collision)
						Sleep(400);

					if (mode.getMode() != LOAD_MODE)
						Sleep(150);

					Sleep(50);
				}
			}
		} while (!this->isGameOver() && !this->isPlayerWon());

		printScoreAndLife(true); // update life after third death.

		//update result file when player end screen
		mode.doResult(timer, FINISH_SCREEN);
	}

	system("cls");
	
	// print after game in silent mode.
	if (mode.getSilentStatus()) {
		(loadModeSucced) ? cout << "Test passed!!!" : cout << "ERROR: Problem occured when trying running silent mode." << endl << "Press any key to continue...";
	}
	else { // any other mode.
		if (this->isPlayerWon() && loadModeSucced)
			cout << "Congratulations, you won!! (Press any key to return main menu)" << endl << endl;

		else if (this->isGameOver())
			cout << "Sorry, you lose.. (Press any key to return main menu)" << endl << endl;

		// if player trying to go load mode but no files exists.
		else if (loadModeSucced == false && mode.getMode() == LOAD_MODE)
			cout << "ERROR: There are no files to load in LOAD MODE" << endl << "Press any key to continue...";
	}

	// wait for key pressed until return to main menu.
	_getch();
	system("cls");
}

// Checking if pacman ate food in the new move and update display of score and hp.
void Game::printScoreAndLife(bool collision) {

	// get Pacman position on board.
	int x = this->player.getPosition().getXPosition();
	int y = this->player.getPosition().getYPosition();

	// check if pacman new position is on food, if so -> update score and make cell sign as empty.
	if (this->board.getCellObject(x, y) == BREADCRUMBS && !collision) {
		// if player ate food update player score.
		this->playerScore += 1;
		this->board.setCellObject(x, y, EMPTY_CELL);
	}

	gotoxy(legend.getYPosition(), legend.getXPosition());
	cout << " HP: " << this->lifePoints << endl;
	gotoxy(legend.getYPosition(), legend.getXPosition()+1);
	cout << " Score: " << this->playerScore + fruit.getBonusScore();
}

void Game::pauseGame(char KEY) {
	if (KEY == ESC) {
		gotoxy(legend.getYPosition(), legend.getXPosition() + 2);
		if (this->gamePause) {
			this->gamePause = FALSE;
			cout << "                    ";
		}
		else {
			this->gamePause = TRUE;
			cout << " Game paused (ESC)";
		}
	}
}

bool Game::isPlayerWon() {
	return (this->playerScore == this->stageTotalScore);
}

bool Game::isGameOver() {
	return (this->lifePoints == 0);
}

bool Game::checkCollision(Mode& mode, int timer) {

	for (int i = 0; i < ghosts.size(); i++)
	{
		// operator overloading
		if (this->player & ghosts[i].getPosition())
		{
			this->lifePoints -= 1; // decrease life by 1.
			mode.doResult(timer, DIED);
			gotoxy(player.getPosition().getYPosition(), player.getPosition().getXPosition());
			cout << 'X';
			return TRUE;
		}

		if (fruit.active() && (fruit.getPosition() == ghosts[i].getPosition()))
			fruit.fruitCollision(true, mode);
	}

	// collision fruit and pacman.
	if(fruit.active() && (fruit.getPosition() == this->player.getPosition()))
		fruit.fruitCollision(false, mode);

	return FALSE;
}

void Game::resumeCharactersToStart() {
	// Move ghosts back to start point.
	for (int j = 0; j < ghosts.size(); j++)
	{
		this->ghosts[j].resumePrevObj(&this->board);
		ghosts[j].goToStartPosition(); // go to start position.
		this->ghosts[j].printCreature();
	}

	// Move pacman back to start point.
	gotoxy(this->player.getPosition().getYPosition(), this->player.getPosition().getXPosition());
	cout << " ";
	this->player.setDirection(DEFAULT);
	this->player.goToStartPosition(); // after death go to start position.
	this->player.printCreature();
}

void Game::setGhostsStrategy(Strategy* strategy) {

	for (auto& ghost : ghosts) {
		ghost.setStrategy(strategy);
	}

	// see if delete
	if (typeid(strategy) != typeid(Novice) && strategy != NULL) {
		strategy->setBFSarray(board.getRowSize(), board.getColSize());
	}

}

Screen& Game::getScreens() {
	return this->screens;
}