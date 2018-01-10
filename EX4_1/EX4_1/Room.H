#ifndef _ROOM_H_
#define _ROOM_H_

#include <string>
#include <iostream>
#include "defs.H"

using std::string;

class Room {
public:
	// Constructor
	Room(unsigned int num, unsigned int size);
	//~Room();

	// Methods
	unsigned int getNum() const;
	bool getIsOccupied() const;
	void setOccupy();
	void setEvacuate();
	void print() const;

protected:
	unsigned int num_;
	unsigned int size_;
	bool occupied_;
};

#endif
