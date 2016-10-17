# Process-Scheduling

Modeled Round Robin Scheduling and Completely Fair Scheduling strategies and optimized the efficiency using data structures such as binary search trees and red black tree (Fast Round Robin Scheduling and Fast Completely Fair Scheduling). The model was used to compare the strengths and weaknesses of those process scheduling strategies.(C++)

It contains 1 main program and the command 'make all' will compile the entire project. Alternatively, the program may compile according to the directions below.


---schedulesim---
To compile: make schedulesim
To run: ./schedulesim <number of CPU bound processes> <number of IO bound processes> <number of cycles to simulate> 
Description:
The schedulesim program takes three command-line parameters: <number of CPU bound processes>, <number of IO bound processes>,  and <number of cycles to simulate>. It creates a RoundRobin scheduler, a FastRoundRobin scheduler, a CompletelyFair  scheduler, and a FastCompletelyFair scheduler, and simulates process scheduling with those four schedulers and prints the results of the simulation.
