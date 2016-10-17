#ifndef RBT_MULTIMAP
#define RBT_MULTIMAP

#include "BSTMultimap.h"
#include "RBTNode.h"

#include <string>
#include <fstream>
#include <queue>
#include <iostream>
#include <map>

using namespace std;

template <class key_t, class val_t>
class RBTMultimap : public BSTMultimap<key_t, val_t>
{
  
  protected:
  
   //Performs the rotate left operation
   //(assumes node has a right child)
   virtual void rotateLeft(BSTNode<key_t, val_t>* node);

   //Performs the rotate right operation
   //(assumes node has a left child)
   virtual void rotateRight(BSTNode<key_t, val_t>* node);
   
   //Fix up the tree after an insert
   //(assumes insertedNode is red)
   virtual void insertFixup(RBTNode<key_t, val_t>* insertedNode);
   
   //Fix up the tree after deleting a node
   //ReplacementNode is the node that replaced the deleted node
   //(possibly the sentinel)
   virtual void deleteFixup(RBTNode<key_t, val_t>* replacementNode);

   //Puts replacementNode in nodeToReplace's position in the tree
   //(replacementNode takes its children along with it)
   //Assumes nodeToReplace is a real node (not the sentinel)
   virtual void transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode);
  
  public:
   //Creates an empty red-black tree
   RBTMultimap();
   virtual ~RBTMultimap();

   //Inserts (key, value) into the multimap
   virtual void insert(const key_t& key, const val_t& value);
   
   //Removes the key/value pair pointed to by pos
   //(if pos is off the end, does nothing)
   //Returns an iterator pointing to the next node after the
   //deleted node
   virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);

   //Prints the tree in the "dot" format for visualization
   //using graphviz
   //NOTE: Requires that keys are streamable (values are not printed)
   virtual void printDOT(std::string filename);
};

//////////////////////////////////////////
//RBTMultimap implementation begins here//
//////////////////////////////////////////

template <class key_t, class val_t>
void RBTMultimap<key_t, val_t>::printDOT(std::string filename)
{
   using namespace std;
   ofstream fout(filename.c_str());

   long long counter = 1;
   map<RBTNode<key_t, val_t>*, long long> nodeToCounter;
   nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] = counter;
   counter++;

   fout << "digraph RBTMultimap {" << endl;

   fout << "\t node" << nodeToCounter[dynamic_cast<RBTNode<key_t, val_t>* >(this->sentinel)] << " [label=\"nil\", style=filled, color=grey, fontcolor=white];" << endl;

   if(this->root != this->sentinel)
   {
      RBTNode<key_t, val_t>* rt = dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
      if(!nodeToCounter[rt])
      {
	 nodeToCounter[rt] = counter;
	 counter++;
      }
      if(!nodeToCounter[rt->getParent()])
      {
	 nodeToCounter[rt->getParent()] = counter;
	 counter++;
      }
      fout << "\t node" << nodeToCounter[rt] << " -> node" << nodeToCounter[rt->getParent()] << " [constraint=false, tailport=n, headport=s";
      if(rt->getParent() == this->sentinel)
      {
	 fout << ", color=grey];" << endl;
      }
      else
      {
	 //The root's parent is something weird!! Make the arrow orange so it sticks out
	 fout << ", color=orange];" << endl;
      }

      map<RBTNode<key_t, val_t>*, bool> printed;
   
      queue<RBTNode<key_t, val_t>* > q;
      q.push(rt);
      while(!q.empty())
      {
	 RBTNode<key_t, val_t>* node = q.front();
	 q.pop();

	 printed[node] = true;
      
	 //Set up node's appearance
	 if(!nodeToCounter[node])
	 {
	    nodeToCounter[node] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " [label=\"k: " << node->getKey() << "\", style=filled, color=";
	 if(node->getColor())
	 {
	    fout << "red";
	 }
	 else
	 {
	    fout << "black, fontcolor=white";
	 }
	 fout << "];" << endl;

	 //Set up child links
	 //First the left node
	 if(!nodeToCounter[node->getLeftChild()])
	 {
	    nodeToCounter[node->getLeftChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getLeftChild()] << " [tailport=sw";    
	 if(node->getLeftChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getLeftChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getLeftChild());
	 }

	 if(node->getLeftChild() != this->sentinel)
	 {
	    if(node->getLeftChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getLeftChild()->getParent()])
	       {
		  nodeToCounter[node->getLeftChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getLeftChild()] << " -> node" << nodeToCounter[node->getLeftChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }

	 //Now the right node
	 if(!nodeToCounter[node->getRightChild()])
	 {
	    nodeToCounter[node->getRightChild()] = counter;
	    counter++;
	 }
	 fout << "\t node" << nodeToCounter[node] << " -> node" << nodeToCounter[node->getRightChild()] << " [tailport=se";    
	 if(node->getRightChild() == this->sentinel)
	 {
	    fout << ", color=grey";
	 }
	 else if(printed[node->getRightChild()])
	 {
	    fout << ", color=orange";
	 }
	 else
	 {
	    q.push(node->getRightChild());
	 }

	 if(node->getRightChild() != this->sentinel)
	 {
	    if(node->getRightChild()->getParent() == node)
	    {
	       //The child's parent pointer points right back,
	       //so draw the second arrow
	       fout << ", dir=both];" << endl;
	    }
	    else
	    {
	       //The child node's parent pointer is not correct!
	       //Draw it in orange so it sticks out
	       fout << "];" << endl;
	       if(!nodeToCounter[node->getRightChild()->getParent()])
	       {
		  nodeToCounter[node->getRightChild()->getParent()] = counter;
		  counter++;
	       }
	       fout << "\t node" << nodeToCounter[node->getRightChild()] << " -> node" << nodeToCounter[node->getRightChild()->getParent()] << " [tailport=n, color=orange];" << endl;
	    }
	 }
	 else
	 {
	    fout << "];" << endl;
	 }
      }
   }
   fout << "}" << endl;
}

template <class key_t, class val_t>
RBTMultimap<key_t,val_t>::RBTMultimap() : BSTMultimap<key_t,val_t>()
{
  key_t key;
  val_t val;
  RBTNode<key_t,val_t>* newNode = new RBTNode<key_t,val_t>(key,val,false);
  this->sentinel = newNode;
  this->root = this->sentinel;
}

template <class key_t, class val_t>
RBTMultimap<key_t,val_t>::~RBTMultimap()
{
  this->clear();
  delete this->sentinel;
}

template <class key_t, class val_t>
void RBTMultimap<key_t,val_t>::insert(const key_t& key, const val_t& value)
{
  RBTNode<key_t,val_t>* newNode = new RBTNode<key_t,val_t>(key,value,true);
  this->insertNode(newNode);
  insertFixup(newNode);
}

template <class key_t, class val_t>
void RBTMultimap<key_t,val_t>::rotateLeft(BSTNode<key_t, val_t>* node)
{
  BSTNode<key_t, val_t>* parent = node->getParent();
  BSTNode<key_t, val_t>* right = node->getRightChild();
  BSTNode<key_t, val_t>* rightLeft = right->getLeftChild();

  node->setRightChild(rightLeft);
  if (rightLeft != this->sentinel)
  {
    rightLeft->setParent(node);
  }

  right->setParent(parent);
  if (parent == this->sentinel)
  {
    this->root = right;
  }
  else if (node == parent->getLeftChild())
  {
    parent->setLeftChild(right);
  }
  else
  {
    parent->setRightChild(right);
  }

  right->setLeftChild(node);
  node->setParent(right);
}


template <class key_t, class val_t>   
void RBTMultimap<key_t,val_t>::rotateRight(BSTNode<key_t, val_t>* node)
{
  BSTNode<key_t, val_t>* parent = node->getParent();
  BSTNode<key_t, val_t>* left = node->getLeftChild();
  BSTNode<key_t, val_t>* leftRight = left->getRightChild();

  node->setLeftChild(leftRight);
  if (leftRight != this->sentinel)
  {
    leftRight->setParent(node);
  }

  left->setParent(parent);
  if (parent == this->sentinel)
  {
    this->root = left;
  }
  else if (node == parent->getLeftChild())
  {
    parent->setLeftChild(left);
  }
  else
  {
    parent->setRightChild(left);
  }

  left->setRightChild(node);
  node->setParent(left);
}

template <class key_t, class val_t>   
void RBTMultimap<key_t,val_t>::insertFixup(RBTNode<key_t, val_t>* insertedNode)
{   
  RBTNode<key_t,val_t>* root = dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
  RBTNode<key_t,val_t>* parent;
  RBTNode<key_t,val_t>* grandParent;
  RBTNode<key_t,val_t>* uncle;
  while (insertedNode->getParent()->getColor() == true)
  {
    parent = insertedNode->getParent();
    grandParent = parent->getParent();
    if (parent == grandParent->getLeftChild())
    {
      uncle = grandParent->getRightChild();
      if (uncle->getColor() == true)
      {
        parent->setColor(false);
        uncle->setColor(false);
        grandParent->setColor(true);
        insertedNode = grandParent;
      }
      
      else 
      {
        if (insertedNode == parent->getRightChild())
        {
          insertedNode = parent;
          rotateLeft(insertedNode);
        }
        parent = insertedNode->getParent();
        grandParent = parent->getParent();
        parent->setColor(false);
        grandParent->setColor(true);
        rotateRight(grandParent);
      }
    }

    else 
    {
      uncle = grandParent->getLeftChild();
      if (uncle->getColor() == true)
      {
        parent->setColor(false);
        uncle->setColor(false);
        grandParent->setColor(true);
        insertedNode = grandParent;
      }
  
      else 
      {
        if (insertedNode == parent->getLeftChild())
        {
          insertedNode = parent;
          rotateRight(insertedNode);
        }
        parent = insertedNode->getParent();
        grandParent = parent->getParent();
        parent->setColor(false);
        grandParent->setColor(true);
        rotateLeft(grandParent);
      }
    }  
  }
  root = dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
  root->setColor(false);
}

template <class key_t, class val_t>   
void RBTMultimap<key_t,val_t>::transplant(BSTNode<key_t, val_t>* nodeToReplace, BSTNode<key_t, val_t>* replacementNode)
{
  if (nodeToReplace->getParent() == this->sentinel)
  {
    this->root = replacementNode;
  }
  else if (nodeToReplace == nodeToReplace->getParent()->getLeftChild())
  {
    nodeToReplace->getParent()->setLeftChild(replacementNode);
  }
  else
  {
    nodeToReplace->getParent()->setRightChild(replacementNode);
  }
 
  replacementNode->setParent(nodeToReplace->getParent());

}

template <class key_t, class val_t>   
BSTForwardIterator<key_t, val_t> RBTMultimap<key_t,val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos)
{
  BSTNode<key_t,val_t>* removeNd = pos.current;
  RBTNode<key_t,val_t>* removeNdRBT = dynamic_cast<RBTNode<key_t, val_t>* >(removeNd);
  BSTNode<key_t,val_t>* replacementNode;
  bool oriColor = removeNdRBT->getColor();
  BSTNode<key_t,val_t>* leftNd = removeNd->getLeftChild();
  BSTNode<key_t,val_t>* rightNd = removeNd->getRightChild();
  BSTForwardIterator<key_t,val_t> nextIter = pos;
  nextIter.next();
  BSTNode<key_t,val_t>* successor = nextIter.current;
  RBTNode<key_t,val_t>* successorRBT = dynamic_cast<RBTNode<key_t, val_t>* >(successor);

  if (removeNd->getLeftChild() == this->sentinel)
  {
    replacementNode = rightNd;
    transplant(removeNd,rightNd);
  }

  else if (removeNd->getRightChild() == this->sentinel)
  {
    replacementNode = leftNd;
    transplant(removeNd,leftNd);
  }

  else
  { 
    oriColor = successorRBT->getColor();
    replacementNode = successor->getRightChild();
    if (successor->getParent() == removeNd)
    {
      replacementNode->setParent(successor);
    }
    else
    {
       transplant(successor,successor->getRightChild());
       successor->setRightChild(removeNd->getRightChild());
       successor->getRightChild()->setParent(successor);
    }
     
    transplant(removeNd,successor);
    successor->setLeftChild(leftNd);
    leftNd->setParent(successor);
    successorRBT->setColor(removeNdRBT->getColor());
  }

  this->numItems -= 1;
  delete removeNd;
  if (oriColor == false)
  {
    deleteFixup(dynamic_cast<RBTNode<key_t, val_t>* >(replacementNode));
  }
  return nextIter;  
}


template <class key_t, class val_t>   
void RBTMultimap<key_t,val_t>::deleteFixup(RBTNode<key_t, val_t>* replacementNode)
{
  RBTNode<key_t,val_t>* root = dynamic_cast<RBTNode<key_t, val_t>* >(this->root);
  while ((replacementNode != root) && (replacementNode->getColor() == false))
  {
    RBTNode<key_t,val_t>* parent = replacementNode->getParent();
    if (replacementNode == parent->getLeftChild())
    {
      RBTNode<key_t,val_t>* sibling = parent->getRightChild();
      if (sibling->getColor() == true)
      {
        sibling->setColor(false);
        parent->setColor(true);
        rotateLeft(parent);
        sibling = parent->getRightChild();
      }
      if ((sibling->getLeftChild()->getColor() == false) && (sibling->getRightChild()->getColor() == false))
      {
        sibling->setColor(true);
        replacementNode = parent;
      }
      else
      {
        if (sibling->getRightChild()->getColor() == false)
	{
          sibling->getLeftChild()->setColor(false);
          sibling->setColor(true);
          rotateRight(sibling);
          sibling = parent->getRightChild();
        }
        sibling->setColor(parent->getColor());
        parent->setColor(false);
        sibling->getRightChild()->setColor(false);
        rotateLeft(parent);
        replacementNode = root;
      }
    }

    else 
    {
      RBTNode<key_t,val_t>* sibling = parent->getLeftChild();
      if (sibling->getColor() == true)
      {
        sibling->setColor(false);
        parent->setColor(true);
        rotateRight(parent);
        sibling = parent->getLeftChild();
      }
      if ((sibling->getLeftChild()->getColor() == false) && (sibling->getRightChild()->getColor() == false))
      {
        sibling->setColor(true);
        replacementNode = parent;
      }
      else
      {
        if (sibling->getLeftChild()->getColor() == false)
	{
          sibling->getRightChild()->setColor(false);
          sibling->setColor(true);
          rotateLeft(sibling);
          sibling = parent->getLeftChild();
        }
        sibling->setColor(parent->getColor());
        parent->setColor(false);
        sibling->getLeftChild()->setColor(false);
        rotateRight(parent);
        replacementNode = root;
      }
    }
  }

  replacementNode->setColor(false);
}



#endif
