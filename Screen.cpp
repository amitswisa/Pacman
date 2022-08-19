#include "Screen.h"

bool Screen::isExistScreen(const string& fileName) {

	for (const auto& vec : pacman_screens)
		if (vec.compare(fileName) == 0)
			return true;

	cout << "Error: file was not found in directory." << endl << endl;
	return false;

}

bool Screen::isEmptyFileVector() {
	if (pacman_screens.size() == 0) {
		cout << "Error: There are no screen files to load." << endl << endl;
		return true;
	}
	return false;

}

// Read screens from current folder.
void Screen::getStagesFilesFromDir(const string& dir) {

	for (const auto& entry : fs::directory_iterator(dir))
	{
		filesystem::path filePath(entry.path());

		string fileName = filePath.stem().string(); // get file name
		string fileExt = filePath.extension().string(); // get file extention
		// check if file name contains .screen and its extention is .txt.
		if (fileName.find("pacman_") != string::npos
			&& fileExt.compare(".screen") == 0) {
			pacman_screens.push_back(filePath.filename().string());
		}

	}
}