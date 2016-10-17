#include "Scheduler.h"
#include <iostream>

RoundRobin::RoundRobin()
{
  procQueue = new ArrayList<Process*>();
}

RoundRobin::~RoundRobin()
{
  delete procQueue;
}

void RoundRobin::addProcess(Process* proc)
{
  procQueue->pushBack(proc);
}

Process* RoundRobin::popNext(int curCycle)
{
  Process* proc = procQueue->getFront();
  procQueue->popFront();
  return proc;
}

FastRoundRobin::FastRoundRobin()
{
  delete procQueue;
  procQueue = new LinkedList<Process*>();
}

CompletelyFair::CompletelyFair()
{
  procTree = new BSTMultimap<int,Process*>();
}

CompletelyFair::~CompletelyFair()
{
  delete procTree;
}

void CompletelyFair::addProcess(Process* proc)
{
  procTree->insert(proc->getCPUTime(),proc);
}

Process* CompletelyFair::popNext(int curCycle)
{
  BSTForwardIterator<int,Process*> myIter = procTree->getMin();
  while (myIter.getValue()->isBlocked(curCycle))
  {
    myIter.next();
  }

  Process* proc = myIter.getValue();
  procTree->remove(myIter);
  return proc;
}

FastCompletelyFair::FastCompletelyFair()
{
  delete procTree;
  procTree = new RBTMultimap<int,Process*>();
}

/*
int main()
{
  Process* a = new CPUBoundProcess(20);
  Process* b = new CPUBoundProcess(30);
  Process* c = new CPUBoundProcess(40);
  RoundRobin d;
  d.addProcess(a);
  d.addProcess(b);
  d.addProcess(c);
  cout << d.popNext()->getID() << endl;
  cout << d.popNext()->getID() << endl;
  cout << d.popNext()->getID() << endl;
  delete a;
  delete b;
  delete c;
}
*/
