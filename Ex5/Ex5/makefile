CXX = g++
CXXFLAGS = -c -g -Wall -std=c++0x
CXXLINK = $(CXX)
LIBS =
OBJS =  ChatNet.o Conversation.o Defs.o main.o MessageBox.o User.o
TARGET = MamatNet
RM = rm -f

# Creating the executable
$(TARGET): $(OBJS)
	$(CXXLINK) -o $(TARGET) $(OBJS) $(LIBS)
	# Creating object files using default rules

# Creating object files using default rules
ChatNet.o: ChatNet.cpp Conversation.h ObjectInterface.h Defs.h ChatNet.h \
 User.h MessageBox.h MySharedPtr.h
Conversation.o: Conversation.cpp Defs.h Conversation.h ObjectInterface.h
Defs.o: Defs.cpp Defs.h ObjectInterface.h
main.o: main.cpp ChatNet.h Defs.h ObjectInterface.h User.h MessageBox.h \
 Conversation.h MySharedPtr.h
MessageBox.o: MessageBox.cpp Defs.h MessageBox.h ObjectInterface.h \
 Conversation.h MySharedPtr.h
User.o: User.cpp User.h ObjectInterface.h Defs.h MessageBox.h \
 Conversation.h MySharedPtr.h

# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *.bak *~ "#"* core
