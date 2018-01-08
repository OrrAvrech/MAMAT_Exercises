# This is a Makefile for the Airport project

CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS =
OBJS = main.o graph.o set.o list.o 
TARGET = robotmmt
RM = rm -f

# Creating the executable Airport
$(TARGET): $(OBJS)
	$(CCLINK) -o $(TARGET) $(OBJS) $(LIBS)
	# Creating object files using default rules

# Creating object files using default rules
graph.o: graph.c graph.h set.h list.h
list.o: list.c list.h
main.o: main.c list.h set.h graph.h
set.o: set.c list.h set.h

# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *.bak *~ "#"* core
