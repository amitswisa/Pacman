#ifndef _UTILS
#define _UTILS

#define EMPTY_CELL ' '
#define PACMAN '@'
#define GHOST '$'
#define WALL '#'
#define BREADCRUMBS '.'
#define LEGEND '&'
#define NOTUNNEL -200
#define NoviceLevel 'c'
#define GoodLevel 'b'
#define BestLevel 'a'
#define DIED 'D'
#define FINISH_SCREEN 'F'

// Pacman files symbols
#define PACMAN_FILE "P"
#define GHOST_FILE "G"
#define FRUIT_FILE "F"
#define FRUIT_APPEAR "AP"
#define FRUIT_DISAPPEAR "DISAP"

#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include <windows.h>

#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

#include "Position.h"

enum {
	LOAD_MODE = 1,
	SAVE_MODE = 0,
	EXIT_GAME = 9,
	INSTRUCTIONS = 8,
	STARTGAME = 1,
	STARTPARTGAME = 2,
	ESC = 27,
	NOT_FOUND = -1,
	DEFAULT = 1,
	LEFT = 'a',
	RIGHT = 'd',
	UP = 'w',
	DOWN = 'x',
	STAY = 's',
	GLEFT = 1,
	GRIGHT = 2,
	GUP = 3,
	GDOWN = 4
};

void gotoxy(int x, int y);
void hideCursor();

#endif