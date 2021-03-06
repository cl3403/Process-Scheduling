#ifndef BST_NODE
#define BST_NODE

template <class key_t, class val_t>
class BSTNode
{
  protected:
   key_t key;
   val_t value;
   BSTNode<key_t,val_t>* leftChild;
   BSTNode<key_t,val_t>* rightChild;
   BSTNode<key_t,val_t>* parent;
   
  public:
   BSTNode(const key_t& key, const val_t& value);
   virtual ~BSTNode() {};

   virtual const val_t& getValue() const;
   virtual void setValue(const val_t& newValue);

   virtual const key_t& getKey() const;
   virtual void setKey(const key_t& newKey);

   virtual BSTNode<key_t,val_t>* getLeftChild();
   virtual void setLeftChild(BSTNode<key_t,val_t>* newLeftChild);

   virtual BSTNode<key_t,val_t>* getRightChild();
   virtual void setRightChild(BSTNode<key_t,val_t>* newRightChild);

   virtual BSTNode<key_t,val_t>* getParent();
   virtual void setParent(BSTNode<key_t,val_t>* newParent);
};


template <class key_t, class val_t>
BSTNode<key_t,val_t>::BSTNode(const key_t& key, const val_t& value)
{
   this->key = key;
   this->value = value;
   leftChild = 0;
   rightChild = 0;
   parent = 0;
}

template <class key_t, class val_t>
const val_t& BSTNode<key_t,val_t>::getValue() const
{
   return value;
}

template <class key_t, class val_t>
void BSTNode<key_t,val_t>::setValue(const val_t& newValue)
{
   value = newValue;
}

template <class key_t, class val_t>
const key_t& BSTNode<key_t,val_t>::getKey() const 
{
   return key;
}

template <class key_t, class val_t>
void BSTNode<key_t,val_t>::setKey(const key_t& newKey)
{
   key = newKey;
}

template <class key_t, class val_t>
BSTNode<key_t,val_t>* BSTNode<key_t,val_t>::getLeftChild()
{
   return leftChild;
}

template <class key_t, class val_t>
void BSTNode<key_t,val_t>::setLeftChild(BSTNode<key_t,val_t>* newLeftChild)
{
   leftChild = newLeftChild;
}

template <class key_t, class val_t>
BSTNode<key_t,val_t>* BSTNode<key_t,val_t>::getRightChild()
{
   return rightChild;
}

template <class key_t, class val_t>
void BSTNode<key_t,val_t>::setRightChild(BSTNode<key_t,val_t>* newRightChild)
{
   rightChild = newRightChild;
}

template <class key_t, class val_t>
BSTNode<key_t,val_t>* BSTNode<key_t,val_t>::getParent()
{
   return parent;
}

template <class key_t, class val_t>
void BSTNode<key_t,val_t>::setParent(BSTNode<key_t,val_t>* newParent)
{
   parent = newParent;
}

#endif
