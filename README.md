# Process-Scheduling

---schedulesim---
To compile: make schedulesim
To run: ./schedulesim <number of CPU bound processes> <number of IO bound processes> <number of cycles to simulate> 
Description:
The schedulesim program takes three command-line parameters: <number of CPU bound processes>, <number of IO bound processes>,  and <number of cycles to simulate>. It creates a RoundRobin scheduler, a FastRoundRobin scheduler, a CompletelyFair  scheduler, and a FastCompletelyFair scheduler, and simulates process scheduling with those four schedulers and prints the results of the simulation.
