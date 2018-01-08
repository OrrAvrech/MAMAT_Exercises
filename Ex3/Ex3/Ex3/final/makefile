# This is a Makefile for the Airport project

CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS =
OBJS = main.o airport.o runway.o flight.o 
TARGET = airport
RM = rm -f

# Creating the executable Airport
$(TARGET): $(OBJS)
	$(CCLINK) -o $(TARGET) $(OBJS) $(LIBS)
	# Creating object files using default rules

# Creating object files using default rules
main.o: main.c airport.h runway.h flight.h ex2.h
airport.o: airport.c airport.h runway.h flight.h ex2.h
runway.o: runway.c runway.h flight.h ex2.h
flight.o: flight.c flight.h ex2.h

# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *.bak *~ "#"* core
