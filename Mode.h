#ifndef MODE
#define MODE
#include "Utils.h"

class Mode
{
	private:
		int gameMode; // Save Mode = 0, Load Mode = 1;
		bool silent;
		fstream stepsFile, resultFile;

	public:
		//Constructors
		Mode(int argv, char** argc);

		~Mode() {
			// close prev steps file if open.
			if (stepsFile.is_open())
				stepsFile.close();

			// close prev result file if open.
			if (resultFile.is_open())
				resultFile.close();
		}

		//functions
		int getMode() const;
		void deletePrev();
		void initFiles(const string& screen_name);
		void doResult(int timer, char status);
		void doSteps(string creature, char direction = 'e');
		char getPacmanMove();
		Position getGhostMove(Position& prevPos);
		fstream& getStepsFile();
		void fixPosition(char directrion, Position& newPos);
		Position getFruitMove(Position& prevPos);
		bool getSilentStatus() const;
		void closeFiles();
		void wrongFiles();
};
#endif