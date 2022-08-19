#ifndef _POSITION
#define _POSITION

class Position {
private:
	int x, y;

public:
	// Operator override
	bool operator==(Position& ghostPos) {
		if (this->getXPosition() == ghostPos.getXPosition()
			&& this->getYPosition() == ghostPos.getYPosition())
			return true;

		return false;
	};
	Position() :x(-1), y(-1) {};
	Position(int x, int y);
	int getXPosition();
	int getYPosition();
	void setPosition(int x, int y);
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
};

#endif