#Artillery alpha

OBJS = artillery.o artlib.o
CC = g++
CFLAGS = -g -std=c++11

artillery : $(OBJS)
	g++ $(OBJS) -o artillery

artillery.o : artillery.cpp artlib.h Makefile
	$(CC) $(CFLAGS) -c artillery.cpp
artlib.o : artlib.cpp Makefile
	$(CC) $(CFLAGS) -c artlib.cpp

