all: prog

prog: main.o priority_queue_min.o
	g++ main.o priority_queue_min.o -o prog

main.o: main.cpp priority_queue_min.h
	g++ -c main.cpp

priority_queue_min.o: priority_queue_min.cpp priority_queue_min.h
	g++ -c priority_queue_min.cpp

clean:
	rm *.o prog
