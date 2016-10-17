#include "Scheduler.h"
#include "Process.h"
#include <cstdlib>
#include <chrono>
#include <iostream>

using namespace std;

double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles)
{
  ArrayList<Process*> CPUList(numCPUBound);
  ArrayList<Process*> IOList(numIOBound);
  for (int i = 1; i <= numCPUBound; i++)
  {
    Process* a = new CPUBoundProcess(i);
    CPUList.pushBack(a);
    sched->addProcess(a);
  }

  for (int j = 1; j <= numIOBound; j++)
  {
    Process* b = new IOBoundProcess(j);
    IOList.pushBack(b);
    sched->addProcess(b);
  }

  int counter = 0;
  int currentCycle = 0;
  auto startTime = chrono::system_clock::now();

  while (currentCycle < numCycles)
  {
    Process* proc = sched->popNext(currentCycle);
    counter += 1;
    currentCycle += proc->simulate(currentCycle,10);
    sched->addProcess(proc);
  }

  auto endTime = chrono::system_clock::now();
  auto dur = endTime - startTime;
  auto durMS = chrono::duration_cast<chrono::nanoseconds>(dur);
  double elapsed = durMS.count();
  
  double* result = new double[5];
  double avgTime = elapsed / counter;
  result[0] = avgTime;
  
  double avgCPU = 0;
  double avgIO = 0;
  double avgWaitCPU = 0;
  double avgWaitIO = 0;
 
  
  for (int i = 0; i < numCPUBound; i++)
  {
    CPUList.getItem(i)->simulate(currentCycle,0);
    avgCPU += CPUList.getItem(i)->getCPUTime();
    avgWaitCPU += CPUList.getItem(i)->getWaitTime();
    delete CPUList.getItem(i);
  }

  for (int j = 0; j < numIOBound; j++)
  {
    IOList.getItem(j)->simulate(currentCycle,0);
    avgIO += IOList.getItem(j)->getCPUTime();
    avgWaitIO += IOList.getItem(j)->getWaitTime();
    delete IOList.getItem(j);
  }

  result[1] = avgCPU / numCPUBound;
  result[2] = avgWaitCPU / numCPUBound;
  result[3] = avgIO / numIOBound;
  result[4] = avgWaitIO / numIOBound;

  return result;
}

int main(int argc, char** argv)
{
  int numCPUBound = atoi(argv[1]);
  int numIOBound = atoi(argv[2]);
  int numCycles = atoi(argv[3]);
  
  
  RoundRobin* schedRR = new RoundRobin();
  FastRoundRobin* schedFRR = new FastRoundRobin();
  CompletelyFair* schedCF = new CompletelyFair();
  FastCompletelyFair* schedFCF = new FastCompletelyFair();

  ArrayList<Scheduler*> schedArr;
  schedArr.pushBack(schedRR);
  schedArr.pushBack(schedFRR);
  schedArr.pushBack(schedCF);
  schedArr.pushBack(schedFCF);

  string strArr[] = {"Using RoundRobin Scheduler","Using FastRoundRobin Scheduler","Using CompletelyFair Scheduler","Using FastCompletelyFair Scheduler"};
  for (int i = 0; i < 4; i++)
  {
    double* result = simulate(schedArr.getItem(i),numCPUBound,numIOBound,numCycles);
    cout << strArr[i] << endl;
    cout << "the overhead of the scheduler on each insertion/removal of a process " << result[0] << endl;
    cout << "the average CPU time of all CPU-bound processes " << result[1] << endl;
    cout << "the average wait time of all CPU-bound processes " << result[2] << endl;
    cout << "the average CPU time of all I/O-bound processes " << result[3] << endl;
    cout << "the average wait time of all I/O-bound processes " << result[4] << endl;
    delete[] result;
  }

  delete schedRR;
  delete schedFRR;
  delete schedCF;
  delete schedFCF;
  }
