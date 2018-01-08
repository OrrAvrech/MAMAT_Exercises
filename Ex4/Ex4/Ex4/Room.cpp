#include "Room.H"
#include "defs.H"
#include <iostream>

using std::cout;
using std::endl;
using std::boolalpha;

Room::Room(int num, int size) : num_(num), size_(size), occupied_(false) { }

int Room::getNum() const { return num_; }

bool Room::getIsOccupied() const { return occupied_; }

void Room::setOccupy() { occupied_ = true; }

void Room::setEvacuate() { occupied_ = false; }

void Room::print() const
{
	cout << "Number : " << num_ << endl;
	cout << "Size : " << size_ << " square meters" << endl;
	cout << boolalpha << "Is Occupied : " << occupied_ << endl;
}


