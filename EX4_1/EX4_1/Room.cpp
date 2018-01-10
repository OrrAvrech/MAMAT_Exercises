#include "Room.H"
#include "defs.H"
#include <iostream>

using std::cout;
using std::endl;
using std::boolalpha;

Room::Room(unsigned int num, unsigned int size) : num_(num), size_(size), occupied_(false) { }

unsigned int Room::getNum() const { return num_; }

bool Room::getIsOccupied() const { return occupied_; }

void Room::setOccupy() { occupied_ = true; }

void Room::setEvacuate() { occupied_ = false; }

void Room::print() const
{
	cout << "Number : " << num_ << endl
		 << "Size : " << size_ << " square meters " << endl
		 << boolalpha << "Is Occupied : " << std::boolalpha << occupied_ << endl;
}


