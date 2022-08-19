/*  Pacman project by:
  Hila Ezra  - 207298894
  Amit Swisa - 315507723  */

#include "GameManager.h"
#include "Mode.h"

void main(int argc, char** argv)
{
	Mode mode(argc, argv);
	GameManager gameManager;
	gameManager.displayMenu(mode);
}