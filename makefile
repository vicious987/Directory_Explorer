CXX=g++
CFLAGS=-std=c++17 -Wall
OBJ=main.o

main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp

clean:
	rm *.o output
