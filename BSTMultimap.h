#ifndef BSTMULTIMAP
#define BSTMULTIMAP

#include "BSTNode.h"
#include "BSTForwardIterator.h"
#include <queue>
#include <iostream>

using namespace std;

template  <class key_t, class val_t>
class BSTMultimap
{
  protected:
   BSTNode<key_t,val_t>* root;
   BSTNode<key_t,val_t>* sentinel;
   int numItems;
   void transplant(BSTNode<key_t,val_t>* deleteNode, BSTNode<key_t,val_t>* childNode,BSTNode<key_t,val_t>* prtNode);
   virtual void insertNode(BSTNode <key_t,val_t>* newNode);
   
  public:
   BSTMultimap();
   virtual ~BSTMultimap();
   
   virtual void insert(const key_t& key, const val_t& val);
   virtual int getSize() const;
   virtual bool isEmpty() const;
   virtual void printTree() const;
   virtual bool contains(const key_t& key) const;
   virtual void clear();
   virtual BSTForwardIterator<key_t,val_t> getMin() const;
   virtual BSTForwardIterator<key_t,val_t> getMax() const;
   virtual BSTForwardIterator<key_t,val_t> findFirst(const key_t& key) const;
   virtual BSTForwardIterator<key_t,val_t> remove(const BSTForwardIterator<key_t,val_t>& pos);
};


template <class key_t, class val_t>
BSTMultimap<key_t,val_t>::BSTMultimap()
{
  sentinel = 0;
  root = sentinel;
  numItems = 0;
}

template <class key_t, class val_t>
BSTMultimap<key_t,val_t>::~BSTMultimap()
{
  clear();
}


template <class key_t, class val_t>
void BSTMultimap<key_t,val_t>::insert(const key_t& key, const val_t& val)
{
  BSTNode<key_t,val_t>* newNode = new BSTNode<key_t,val_t>(key,val);
  insertNode(newNode);
}


template <class key_t, class val_t>
int BSTMultimap<key_t,val_t>::getSize() const
{
  return numItems;
}

template <class key_t, class val_t>
bool BSTMultimap<key_t,val_t>::isEmpty() const
{
  if (numItems == 0)
  {
    return true;
  }
  
  return false;
}

template <class key_t, class val_t>
void BSTMultimap<key_t,val_t>::printTree() const
{
  queue<BSTNode<key_t,val_t>*> q;
  q.push(root);
  while ((!q.empty()) && (!isEmpty()))
  {
    BSTNode<key_t,val_t>* popNode = q.front();
    cout << popNode->getKey() << endl;
    cout << popNode->getValue() << endl;
    cout << endl;
    q.pop();
    if (popNode->getLeftChild() != sentinel)
    {
      q.push(popNode->getLeftChild());
    }
    if (popNode->getRightChild() != sentinel)
    {
      q.push(popNode->getRightChild());
    }
  }   
}

template <class key_t, class val_t>
bool BSTMultimap<key_t,val_t>::contains(const key_t& key) const
{
  BSTNode<key_t,val_t>* tracePtr = root;
  while ((tracePtr != sentinel) && (key != tracePtr->getKey()))
  {
    if (key < tracePtr->getKey())
    {
      tracePtr = tracePtr->getLeftChild();
    }
    else
    {
      tracePtr = tracePtr->getRightChild();
    }
  }

  if (tracePtr != sentinel)
  {  
    return true;
  }

  return false;
}

template <class key_t, class val_t>
void BSTMultimap<key_t,val_t>::clear()
{
  queue<BSTNode<key_t,val_t>*> q;
  q.push(root);
  while ((!q.empty()) && (!isEmpty()))
  {
    BSTNode<key_t,val_t>* popNode = q.front();
    q.pop();
    if (popNode->getLeftChild() != sentinel)
    {
      q.push(popNode->getLeftChild());
    }
    if (popNode->getRightChild() != sentinel)
    {
      q.push(popNode->getRightChild());
    }
    delete popNode;
    numItems -= 1;
  }   

  root = sentinel;
}

template <class key_t, class val_t>
BSTForwardIterator<key_t,val_t> BSTMultimap<key_t,val_t>::getMin() const
{
  if (isEmpty())
  {
    BSTForwardIterator<key_t,val_t> minIter(sentinel,sentinel);
    return minIter;  
  }

  else
  {
    BSTNode<key_t,val_t>* tracePtr = root;
    while (tracePtr->getLeftChild() != sentinel)
    {
      tracePtr = tracePtr->getLeftChild();
    }
  
    BSTForwardIterator<key_t,val_t> minIter(tracePtr,sentinel);
    return minIter;  
  }
}

template <class key_t, class val_t>
BSTForwardIterator<key_t,val_t> BSTMultimap<key_t,val_t>::getMax() const
{
  if (isEmpty())
  {
    BSTForwardIterator<key_t,val_t> maxIter(sentinel,sentinel);
    return maxIter;  
  }

  else
  {
    BSTNode<key_t,val_t>* tracePtr = root;
    while (tracePtr->getRightChild() != sentinel)
    {
      tracePtr = tracePtr->getRightChild();
    }
  
    BSTForwardIterator<key_t,val_t> maxIter(tracePtr,sentinel);
    return maxIter;  
  }
}

template <class key_t, class val_t>
BSTForwardIterator<key_t,val_t> BSTMultimap<key_t,val_t>::findFirst(const key_t& key) const
{
  BSTNode<key_t,val_t>* tracePtr = root;
  BSTNode<key_t,val_t>* firstNd = sentinel;
  while (tracePtr != sentinel)
  {
    if (key <= tracePtr->getKey())
    {
      if (key == tracePtr->getKey())
      {
        firstNd = tracePtr;
      }
      tracePtr = tracePtr->getLeftChild();
    }
    else
    {
      tracePtr = tracePtr->getRightChild();
    }
  }

  BSTForwardIterator<key_t,val_t> firstIter(firstNd,sentinel);
  return firstIter;  
}

template <class key_t, class val_t>
  void BSTMultimap<key_t,val_t>::transplant(BSTNode<key_t,val_t>* deleteNode,BSTNode<key_t,val_t>* childNode,BSTNode<key_t,val_t>* prtNode)
{
  if (prtNode == sentinel)
  {
    root = childNode;
  }
  else if (deleteNode == prtNode->getLeftChild())
  {
    prtNode->setLeftChild(childNode);
  }
  else
  {
    prtNode->setRightChild(childNode);      
  }

  if (childNode != sentinel)
  {
    childNode->setParent(prtNode);
  }

}

template <class key_t, class val_t>
BSTForwardIterator<key_t,val_t> BSTMultimap<key_t,val_t>::remove(const BSTForwardIterator<key_t,val_t>& pos)
{
  BSTNode<key_t,val_t>* removeNd = pos.current;
  BSTNode<key_t,val_t>* leftNd = removeNd->getLeftChild();
  BSTNode<key_t,val_t>* rightNd = removeNd->getRightChild();
  BSTNode<key_t,val_t>* prtNd = removeNd->getParent();
  BSTForwardIterator<key_t,val_t> nextIter = pos;
  nextIter.next();
  BSTNode<key_t,val_t>* successor = nextIter.current;
  if (removeNd->getLeftChild() == sentinel)
  {
    transplant(removeNd,rightNd,prtNd);
  }

  else if (removeNd->getRightChild() == sentinel)
  {
    transplant(removeNd,leftNd,prtNd);
  }

  else
  { 
    if (successor->getParent() != removeNd)
    {
      transplant(successor,successor->getRightChild(),successor->getParent());
      successor->setRightChild(rightNd);
      rightNd->setParent(successor);
    }
    transplant(removeNd,successor,prtNd);
    successor->setLeftChild(leftNd);
    leftNd->setParent(successor);
  }

  numItems -= 1;
  delete removeNd;
  return nextIter;  
}

template <class key_t, class val_t>
void BSTMultimap<key_t,val_t>::insertNode(BSTNode <key_t,val_t>* newNode)
{
  BSTNode<key_t,val_t>* tracePtr = root;
  BSTNode<key_t,val_t>* parent = sentinel;

  while (tracePtr != sentinel)
  {  
    parent = tracePtr;
    if (newNode->getKey() < tracePtr->getKey())
    {
      tracePtr = tracePtr->getLeftChild();
    }
    else
    {
      tracePtr = tracePtr->getRightChild();
    }
  }
  
  newNode->setParent(parent);
  if (parent == sentinel)
  {
    root = newNode;
  }
  else if (newNode->getKey() < parent->getKey())
  {
    parent->setLeftChild(newNode);
  }
  else
  {
    parent->setRightChild(newNode);
  }

  newNode->setRightChild(sentinel);
  newNode->setLeftChild(sentinel);
  numItems += 1;
}
   

#endif
