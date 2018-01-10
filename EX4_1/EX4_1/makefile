CC = g++
CXXFLAGS = -g -Wall -std=c++0x
CCLINK = $(CC)
LIBS =
OBJS = main.o Child.o Class.o Office.o Person.o Room.o Teacher.o 
TARGET = Kindergarten
RM = rm -f

# Creating the executable
$(TARGET): $(OBJS)
	$(CCLINK) -o $(TARGET) $(OBJS) $(LIBS)
	# Creating object files using default rules

# Creating object files using default rules
Child.o: Child.C Child.H Person.H defs.H
Class.o: Class.C Class.H defs.H Room.H Child.H Person.H Teacher.H
main.o: main.C Office.H Room.H defs.H Class.H Child.H Person.H Teacher.H
Office.o: Office.C Office.H Room.H defs.H Class.H Child.H Person.H \
 Teacher.H
Person.o: Person.C Person.H
Room.o: Room.C Room.H defs.H
Teacher.o: Teacher.C Teacher.H Person.H

# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *.bak *~ "#"* core
