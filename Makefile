
artillery : artillery.o artlib.o
	g++ artillery.o artlib.o -o artillery

artillery.o : artillery.cpp artlib.h artlib.cpp
	g++ -c artillery.cpp

artlib.o : artlib.cpp
	g++ -c artlib.cpp


	
