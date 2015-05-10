#Artillery alpha

OBJS = artillery.o artlib.o artillery-gui.o
CC = g++
CFLAGS = -g -c -std=c++11
LINKFLAGS = -lSDL2

$(info ========================COMPILING========================)
artillery : $(OBJS)
	g++ $(OBJS) $(LINKFLAGS) -o artillery

artillery.o : artillery.cpp artlib.h artillery-gui.h Makefile
	$(CC) $(CFLAGS) artillery.cpp
artlib.o : artlib.cpp Makefile
	$(CC) $(CFLAGS) artlib.cpp
artillery-gui.o : artillery-gui.cpp
	$(CC) $(CFLAGS) artillery-gui.cpp

