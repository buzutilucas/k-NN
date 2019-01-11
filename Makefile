all: main clean

main: main.o knn.o
	g++ main.o knn.o -o main

main.o: main.cpp
	g++ -c main.cpp -std=c++11

knn.o: knn.cpp knn.h
	g++ -c knn.cpp -std=c++11

clean:
	rm -rf *.o *.h.*

run:
	./main
