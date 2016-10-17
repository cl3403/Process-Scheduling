#ifndef BST_FORWARD_ITERATOR
#define BST_FORWARD_ITERATOR

#include <iostream>
#include "BSTNode.h"

using namespace std;

template <class key_t, class val_t>
class BSTForwardIterator
{
  protected:
   //The node the iterator currently points to
   BSTNode<key_t, val_t>* current;
   //The value representing the non-node
   BSTNode<key_t, val_t>* sentinel;
   
  public:
   BSTForwardIterator(BSTNode<key_t, val_t>* node, BSTNode<key_t, val_t>* sentinel);

   //Points the iterator at the successor of its
   //current node (if current is the sentinel,
   //does nothing).
   virtual void next();

   //Returns true if the iterator has moved past
   //the end of the container (if current is sentinel)
   virtual bool isPastEnd() const;

   //Returns the key of the current node
   virtual const key_t& getKey() const;

   //Returns the value of the current node
   virtual const val_t& getValue() const;
   
   //Sets the value of the current node
   virtual void setValue(const val_t& newVal);

   //Declares BSTMultimap as a friend class
   //(so it can access the protected member current)
   template <class k_t, class v_t> friend class BSTMultimap;
   template <class k_t, class v_t> friend class RBTMultimap;
};

////////////////////////////////////////////////////
//Implementation of BSTForwardIterator begins here//
////////////////////////////////////////////////////

template <class key_t, class val_t>
BSTForwardIterator<key_t,val_t>::BSTForwardIterator(BSTNode<key_t, val_t>* node, BSTNode<key_t, val_t>* sentinel)
{
  current = node;
  this->sentinel = sentinel;
}

template <class key_t, class val_t>
void BSTForwardIterator<key_t,val_t>::next()
{
  if (current != sentinel)
  {
    if (current->getRightChild() != sentinel)
    {
      current = current->getRightChild();
      while (current->getLeftChild() != sentinel)
      {
        current = current->getLeftChild();
      }
    }
    
    else
    {
      BSTNode<key_t,val_t>* parent = current->getParent();
      while ((parent != sentinel) && (current == parent->getRightChild()))
      {
        current = parent;
        parent = parent->getParent();
      }
      
      current = parent;
    }
  }
}

template <class key_t, class val_t>
bool BSTForwardIterator<key_t,val_t>::isPastEnd() const
{
  if (current == sentinel)
  {
    return true;
  }
  return false;
}

template <class key_t, class val_t>
const key_t& BSTForwardIterator<key_t,val_t>::getKey() const
{
  if (current == sentinel)
  {
    cout << "error: current node is sentinel" << endl;
  }
  return current->getKey();
  
}

template <class key_t, class val_t>
const val_t& BSTForwardIterator<key_t,val_t>::getValue() const
{
  if (current == sentinel)
  {
    cout << "error: current node is sentinel" << endl;
  }
  return current->getValue();
}

template <class key_t, class val_t>
void BSTForwardIterator<key_t,val_t>::setValue(const val_t& newVal)
{
  if (current == sentinel)
  {
    cout << "error: current node is sentinel" << endl;
  }
  current->setValue(newVal);  
}


#endif
