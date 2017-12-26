# This is a Makefile for the Airport project

CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
LIBS =
OBJS = graph.o list.o main.o set.o
TARGET = robommt
RM = rm -f

# Creating the executable Airport

$(TARGET): $(OBJS)
	$(CCLINK) -o $(TARGET) $(OBJS) $(LIBS)

  graph.o: graph.c list.h set.h graph.h
  list.o: list.c list.h
  main.o: main.c list.h set.h graph.h
  set.o: set.c list.h set.h

clean:
	$(RM) $(TARGET) *.o *.bak *~ "#"* core
