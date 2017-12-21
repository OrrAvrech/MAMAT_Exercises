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

  airport.o: airport.c ex2.h flight.h runway.h airport.h
  flight.o: flight.c ex2.h flight.h
  main.o: main.c ex2.h flight.h runway.h airport.h
  runway.o: runway.c ex2.h flight.h runway.h
  
# Cleaning old files before new make

clean:
	$(RM) $(TARGET) *.o *.bak *~ "#"* core
