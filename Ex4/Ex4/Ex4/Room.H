#ifndef _ROOM_H_
#define _ROOM_H_

#include <string>
#include <iostream>
#include "defs.H"

using std::string;

class Room {
public:
	// Constructor
	Room(int num, int size);
	//~Room();

	// Methods
	int getNum() const;
	bool getIsOccupied() const;
	void setOccupy();
	void setEvacuate();
	void print() const;

private:
	int num_;
	int size_;
	bool occupied_;
};

#endif
