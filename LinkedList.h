#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "LinkedListNode.h"
#include "List.h"
#include <iostream>

using namespace std;

template <class item_t>
class LinkedList : public List<item_t>
{
  protected:
   LinkedListNode<item_t>* head;
   LinkedListNode<item_t>* tail;
   int size;
   void addToEmpty(LinkedListNode<item_t>* newNode);
   void deleteEmpty(LinkedListNode<item_t>* deleteNode);
   
  public:
   LinkedList();
   virtual ~LinkedList();
   
   virtual void pushBack(const item_t& item);  
   virtual void popBack();
   virtual const item_t& getBack() const;
   
  
   virtual void pushFront(const item_t& item);
   virtual void popFront();
   virtual const item_t& getFront() const;

   
   virtual const item_t& getItem(int index) const;
   virtual void setItem(int index, const item_t& item);
   virtual void insert(int index, const item_t& item);
  
   virtual void remove(int index);
   virtual int getSize() const;
   virtual bool isEmpty() const;
   void print() const;

};


template <class item_t>
LinkedList<item_t>::LinkedList()
{
  head = 0;
  tail = 0;
  size = 0;
}


template <class item_t>
LinkedList<item_t>::~LinkedList()
{
  while (size != 0)
  {
    popBack();
  }
}

template <class item_t>
void LinkedList<item_t>::addToEmpty(LinkedListNode<item_t>* newNode)
{
  head = newNode;
  tail = newNode;
  newNode->setNext(0);
}

template <class item_t>
void LinkedList<item_t>::deleteEmpty(LinkedListNode<item_t>* deleteNode)
{
  head = 0;
  tail = 0;
  delete deleteNode;
  size -= 1;
}

template <class item_t>
void LinkedList<item_t>::pushBack(const item_t& item)
{
  LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(0,item);
  
  if (isEmpty())
  {
    addToEmpty(newNode);
    size += 1;
  }
  
  else
  {
    tail->setNext(newNode);
    tail = newNode;
    size += 1;
  }
}

template <class item_t>
void LinkedList<item_t>::popBack()
{
  LinkedListNode<item_t>* deleteNode = tail;

  if (getSize() == 1)
  {
    deleteEmpty(deleteNode);
  }

  else
  {
    LinkedListNode<item_t>* newTail = head;
    for (int i = 0; i < size - 2; i++)
    {
      newTail = newTail->getNext();
    }
    tail = newTail;
    newTail->setNext(0);
    delete deleteNode;
    size -= 1;
  }
} 

template <class item_t>
const item_t& LinkedList<item_t>::getBack() const
{
  return tail->getItem();
}

template <class item_t>
void LinkedList<item_t>::pushFront(const item_t& item)
{
  LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(0,item);
 
  if (isEmpty())
  {
    addToEmpty(newNode);
    size += 1;
  }

  else
  {
    newNode->setNext(head);
    head = newNode;
    size += 1;
  }
  
}
 
template <class item_t>
void LinkedList<item_t>::popFront()
{
  LinkedListNode<item_t>* deleteNode = head;

  if (getSize() == 1)
  {
    deleteEmpty(deleteNode);
  }

  else
  {
    LinkedListNode<item_t>* newHead = head->getNext();   
    head = newHead;
    delete deleteNode;
    size -= 1;
  }
}

template <class item_t>
const item_t& LinkedList<item_t>::getFront() const
{
  return head->getItem();
}

template <class item_t>
const item_t& LinkedList<item_t>::getItem(int index) const
{
  LinkedListNode<item_t>* myNode = head;
  for (int i = 0; i < index; i++)
  {
    myNode = myNode->getNext();
  }
  
  return myNode->getItem();
}

template <class item_t>
void LinkedList<item_t>::setItem(int index, const item_t& item)
{
  LinkedListNode<item_t>* myNode = head;
  for (int i = 0; i < index; i++)
  {
    myNode = myNode->getNext();
  }
  myNode->setItem(item);
  
}

template <class item_t>
void LinkedList<item_t>::insert(int index, const item_t& item)
{ 
  if (index == 0)
  {
    pushFront(item);
  }

  else if (index == size)
  {
    pushBack(item);
  }

  else
  {
    LinkedListNode<item_t>* preNode = head;
    for (int i = 0; i < index-1; i++)
    {
      preNode = preNode->getNext();
    }
    LinkedListNode<item_t>* nextNode = preNode->getNext();
    LinkedListNode<item_t>* newNode = new LinkedListNode<item_t>(nextNode,item);;
    preNode->setNext(newNode);
    size += 1;
  }
}

template <class item_t>
void LinkedList<item_t>::remove(int index)
{
  if (index == 0)
  {
    popFront();
  }

  else if (index == size-1)
  {
    popBack();
  }

  else
  {
    LinkedListNode<item_t>* preNode = head;
    for (int i = 0; i < index-1; i++)
    {
      preNode = preNode->getNext();
    }
    LinkedListNode<item_t>* removeNode = preNode->getNext();
    LinkedListNode<item_t>* nextNode = removeNode->getNext();
    preNode->setNext(nextNode);
    delete removeNode;
    size -= 1;
  }
}

template <class item_t>
int LinkedList<item_t>::getSize() const
{
  return size;
}

template <class item_t>
bool LinkedList<item_t>::isEmpty() const
{
  if (size == 0)
  {
    return true;
  }
  
  return false;
}

template <class item_t>
void LinkedList<item_t>::print() const
{
  LinkedListNode<item_t>* myNode = head;
  for (int i = 0; i < size - 1; i++)
  {
    cout << myNode->getItem() << "-";
    myNode = myNode->getNext();
  }
  cout << myNode->getItem();
}

#endif
