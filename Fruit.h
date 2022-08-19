#ifndef _FRUIT
#define _FRUIT

#include "Utils.h"
#include "Creature.h"
#include "Board.h"

class Fruit:public Creature {

	private:
		int fruitPoint; // fruit presentive char and value.
		int waitToAppearTime; // timer to hide fruit.
		int scoreAchieved; // total score player achieved with the bonus points.
		bool isActive; // is Fruit appearing on screen. 

	public:
		Fruit():isActive(false), scoreAchieved(0) {
			this->setNewWaitingTime();
		};

		void initFruit(Board* board, vector<Ghost>& ghosts, Pacman& pacman, Position& legend, Mode& mode);
		void setNewWaitingTime();
		void decreaseTimer();
		Position getRandomPosition(Board* board, vector<Ghost>& ghosts, Pacman& pacman, Position& legend);
		void fruitCollision(bool isGhost, Mode& mode);
		void moveRandomly(Board* board, Mode& mode);
		bool active();
		int getBonusScore();
		virtual void printCreature();

};
#endif