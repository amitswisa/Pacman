#ifndef _SCREEN
#define _SCREEN

#include "Utils.h"

class Screen {

	public:
		vector<string> pacman_screens;

		Screen() {
			// load stages from current folder to pacman_files vector.
			this->getStagesFilesFromDir(".");
		};

		~Screen() {
			pacman_screens.clear();
		};

		Screen(string file) { pacman_screens.push_back(file); };

		bool isExistScreen(const string& fileName);
		bool isEmptyFileVector();
		void getStagesFilesFromDir(const string& dir);
};

#endif