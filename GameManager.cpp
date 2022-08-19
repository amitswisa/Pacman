#include "GameManager.h"

void GameManager::displayMenu(Mode& mode) {

	int playerChoice;
	
	// do in load mode.
	if (mode.getMode() == LOAD_MODE)
	{
		// check if no screen loaded.
		if (pacman_files.isEmptyFileVector())
			return;

		pacman = new Game(pacman_files);
		this->runPacman(mode);
	}
	else { // save mode
		do {
			
			cout << "Pacman menu: " << endl;
			cout << "(1) Start a new game" << endl;
			cout << "(2) Start a new game with specific screen" << endl;
			cout << "(8) Present instructions and keys" << endl;
			cout << "(9) EXIT" << endl;

			playerChoice = _getch() - '0'; // decrease '0' asci value from _getch asci value to get key pressed. 
			system("cls");

			// in case user wants to start a game.
			if (playerChoice == STARTGAME || playerChoice == STARTPARTGAME)
			{
				// no screen loaded.
				if (pacman_files.isEmptyFileVector())
					continue;

				// handling single stage situation.
				if (playerChoice == STARTPARTGAME) {

					cout << "Enter file name with .screen extention (Ex: pacman_a.screen): ";
					string temp;
					cin >> temp;

					if (pacman_files.isExistScreen(temp))
						pacman = new Game(Screen(temp));
					
				}
				else 
					pacman = new Game(pacman_files);
				
				// if pacman allocated.
				if (pacman != NULL)
					this->runPacman(mode);

				continue;
			}

			// Game reaction for player's choice.
			switch (playerChoice)
			{
			case INSTRUCTIONS:
				this->printInstructions();
				break;
			case EXIT_GAME:
				this->exitGame();
				break;
			default:
				cout << "Error: invalid choice was selected." << endl;
				break;
			}

		} while (playerChoice != EXIT_GAME);
	}
}

void GameManager::printInstructions() {
	cout << "Instructions and keys:" << endl;
	cout << "The player controls Pac-Man, who must eat all the dots inside an enclosed maze while avoiding the ghosts." << endl
		<< "Eating large flashing dots called 'Power Pellets' causes the ghosts to turn blue, allowing Pac-Man to eat them\nfor bonus points." << endl;
	cout << "\nPlaying keys: \nW - Moving up.\nX - Moving down.\nD - Moving right.\nA - Moving left." << endl << endl;
}

void GameManager::exitGame() {
	exit(0);
}

void GameManager::runPacman(Mode& mode) {

	Strategy* strategy = NULL;

	// delete old ".result" & ".steps" from current directory.
	if (mode.getMode() != LOAD_MODE) {

		if (mode.getMode() == SAVE_MODE)
			mode.deletePrev();

		strategy = this->chooseStrategy();
	}

	pacman->initGame(strategy, mode);
	delete strategy;
	delete pacman;

	// close files if open.
	mode.closeFiles();
}

Strategy* GameManager::chooseStrategy() {
	char level;
	do {
		system("cls");
		cout << "Choose level:" << endl << "(a) Best" << endl << "(b) Good" << endl << "(c) Novice";
		level = _getch();
	} while (level != BestLevel && level != GoodLevel && level != NoviceLevel);

	if (level == NoviceLevel)
		return new Novice();
	else if(level == GoodLevel)
		return new Good();
	else
		return new Best();
}