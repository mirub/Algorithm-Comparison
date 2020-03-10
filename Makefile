CC = g++
CFLAGS = -Wall -Wextra -O2
LDLIBS = -lm

build: algo.o

run: generator
	./generator

algo.o: algo.cpp
	g++ algo.cpp -c $(CFLAGS)

dijkstra.o: dijkstra.cpp
	g++ dijkstra.cpp -c $(CFLAGS)

bellman_ford.o: bellman_ford.cpp
	g++ bellman_ford.cpp -c $(CFLAGS)

johnson.o: johnson.cpp
	g++ johnson.cpp -c $(CFLAGS)

generator.o: generator.cpp
	g++ generator.cpp -c $(CFLAGS)

generator: generator.o algo.o dijkstra.o bellman_ford.o johnson.o
	g++ generator.o algo.o dijkstra.o bellman_ford.o johnson.o $(CFLAGS) -o generator

.PHONY: clean
clean:
	rm -rf *.o
