#include "Position.h"

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Position::getXPosition() {
	return this->x;
}

int Position::getYPosition() {
	return this->y;
}

void Position::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void Position::goLeft() {
	this->y -= 1;
}

void Position::goRight() {
	this->y += 1;
}

void Position::goUp() {
	this->x -= 1;

}

void Position::goDown() {
	this->x += 1;

}