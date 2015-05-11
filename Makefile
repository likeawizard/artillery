#Artillery alpha

OBJS = artillery.o artlib.o artillery-gui.o
CC = g++
CFLAGS = -g -c -std=c++11
LINKFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

$(info ========================COMPILING========================)
artillery : $(OBJS)
	g++ $(OBJS) $(LINKFLAGS) -o artillery

artillery.o : artillery.cpp artlib.h artillery-gui.h
	$(CC) $(CFLAGS) artillery.cpp
artlib.o : artlib.cpp
	$(CC) $(CFLAGS) artlib.cpp
artillery-gui.o : artillery-gui.cpp artillery-gui.h
	$(CC) $(CFLAGS) artillery-gui.cpp

