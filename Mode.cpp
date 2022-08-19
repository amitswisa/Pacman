#include "Mode.h"

#include <sstream>

// Constructor
Mode::Mode(int argc, char** argv) {

	// set by default
	this->gameMode = NOT_FOUND;
	this->silent = false;

	// check amount arguments validation.
	if (argc > 3 || argc <= 1)
		return;

	// check arguments validation for save mode.
	if (strcmp(argv[1], "-save") == 0)
	{
		if (argc > 2)
			return;

		this->gameMode = SAVE_MODE;
	}

	// check arguments validation for load mode.
	if (strcmp(argv[1], "-load") == 0)
	{
		if (argc == 3) {
			if (strcmp(argv[2], "[-silent]") != 0)
				return;
			this->silent = true;
		}

		this->gameMode = LOAD_MODE;
	}

}

int Mode::getMode() const {
	return this->gameMode;
}

void Mode::deletePrev() {
	for (const auto& entry : fs::directory_iterator("."))
	{
		filesystem::path filePath(entry.path());

		string fileExt = filePath.extension().string(); // get file extention
		if (fileExt.compare(".steps") == 0 || fileExt.compare(".result") == 0) {
			filesystem::remove(filePath); // delete file with relevant extention.
		}

	}
}

void Mode::initFiles(const string& screen_name) {

	if (this->getMode() == NOT_FOUND)
		return;

	this->closeFiles();

	//change extantion of screen name and load files
	string toOpen = screen_name.substr(0, screen_name.length()-7); //".screen
	if (this->getMode() == LOAD_MODE) {
		stepsFile.open(toOpen + ".steps", ios::in);
		resultFile.open(toOpen + ".result", ios::in);
	}
	else {
		stepsFile.open(toOpen + ".steps", ios::out|ios::app);
		resultFile.open(toOpen + ".result", ios::out|ios::app);
	}

	//if files not exist load next stage 
	if (!stepsFile.is_open() || !resultFile.is_open())
		throw "next stage";
}

void Mode::doResult(int timer, char status) {
	
	if (getMode() == SAVE_MODE)
	{
		if (status == DIED)
			resultFile << "D " << timer << endl;
		else
		{
			//close prev stage files when loading next stage
			resultFile << "F " << timer << endl;
		}
	}

	if(this->getSilentStatus()) //load mode + silent
	{
		char pacStatus; 
		int statusTime;

		//reading from result file pacman ststus(finish or died) and when
		this->resultFile >> pacStatus >> statusTime;

		if (status != pacStatus || statusTime != timer)
		{
			system("cls");
			cout << "Test failed!!!" << endl;
			exit(0);
		}
	}
}

void Mode::doSteps(string creature, char direction) {

	if (this->getMode() == SAVE_MODE)
	{
		stepsFile << creature;
		if (direction != 'e')
		{
			stepsFile << " " << direction;
		}
		stepsFile << endl;
	}
}

char Mode::getPacmanMove() {

	if (stepsFile.peek() != 'P')
		return PACMAN;

	string hold;
	getline(stepsFile, hold);
	return hold[2];

}

Position Mode::getGhostMove(Position& prevPos) {

	if (stepsFile.peek() != 'G')
		this->wrongFiles();

	Position newPos = prevPos;
	string temp;
	getline(stepsFile, temp);
	char direction = temp[3];

	fixPosition(direction, newPos);
	return newPos;
}

Position Mode::getFruitMove(Position& prevPos) {

	if (stepsFile.peek() != 'F')
		this->wrongFiles();

	Position newPos = prevPos;
	string temp;
	getline(stepsFile, temp);
	
	temp = temp.substr(2, temp.length());

	// in substring there is more then just direction => disappear.
	if (temp.find("DIS") != string::npos)
		return Position(NOT_FOUND, NOT_FOUND);
	else {
		char direction = temp[0];
		fixPosition(direction, newPos);
	}

	return newPos;
}

fstream& Mode::getStepsFile() {
	return this->stepsFile;
}

void Mode::fixPosition(char directrion, Position& newPos) {
	
	switch (directrion)
	{
	case 'w':
		newPos.goUp();
		break;
	case 'x':
		newPos.goDown();
		break;
	case 'a':
		newPos.goLeft();
		break;
	case 'd':
		newPos.goRight();
		break;
	default:
		break;
	}

}

bool Mode::getSilentStatus() const {
	return this->silent;
}

void Mode::closeFiles() {
	// close prev steps file if open.
	if (stepsFile.is_open())
		stepsFile.close();

	// close prev result file if open.
	if (resultFile.is_open())
		resultFile.close();
}

void Mode::wrongFiles() {
	
	system("cls");
	cout << "ERROR: a problem occure regarding given steps file.";
	exit(1);
	
}