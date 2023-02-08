CC = g++
CFLAGS = -std=c++11

all:311510182.o
311510182.o:311510182.cpp graph.o
	$(CC) $(CFLAGS) 311510182.cpp graph.o -o 311510182.o
graph.o:graph.cpp
	$(CC) $(CFLAGS) -c graph.cpp
clean:
	rm -rf *.o