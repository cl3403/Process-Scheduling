Chang Liu
CPS 222 Project 2

Files submitted:

List.h
ArrayList.h
LinkedList.h
LinkedListNode.h
BSTMultimap.h
BSTNode.h
BSTForwardIterator.h
RBTMultimap.h
RBTNode.h
Scheduler.cc/h
Process.cc/h
schedulesim.cc
Makefile
cputimes.pdf
timing.pdf
readme.txt
Project 2 Cover Sheet.docx

This project contains only 1 main program and the command 'make' will compile the entire project. Alternatively, you may compile according to the directions below.

---schedulesim---
To compile: make schedulesim
To run: ./schedulesim <number of CPU bound processes> <number of IO bound processes> <number of cycles to simulate> 
Description:
The schedulesim program takes three command-line parameters: <number of CPU bound processes>, <number of IO bound processes>,  and <number of cycles to simulate>. It creates a RoundRobin scheduler, a FastRoundRobin scheduler, a CompletelyFair  scheduler, and a FastCompletelyFair scheduler, and simulates process scheduling with those four schedulers and prints the results of the simulation.



