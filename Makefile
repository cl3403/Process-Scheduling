OPTS = -g -Wall -std=c++11

schedulesim: schedulesim.cc Scheduler.o Process.o
	g++ ${OPTS} -o schedulesim schedulesim.cc Scheduler.o Process.o

Scheduler.o: Scheduler.cc Scheduler.h ArrayList.h LinkedList.h LinkedListNode.h List.h BSTNode.h BSTMultimap.h BSTForwardIterator.h RBTNode.h RBTMultimap.h
	g++ ${OPTS} -c Scheduler.cc

Process.o: Process.cc Process.h
	g++ ${OPTS} -c Process.cc
