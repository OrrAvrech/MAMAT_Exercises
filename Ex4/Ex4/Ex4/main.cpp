#include "Room.H"

int main() {

	Room r(15, 60);
	r.print();
	r.setOccupy();
	r.print();
	return 0;
}