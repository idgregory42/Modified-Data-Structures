#if !defined (BINARYSEARCHTREE_H)
#define BINARYSEARCHTREE_H

#include "BinaryTreeIterator.h"
#include "TreeNode.h"
#include "Text.h"



#include <string>
using namespace std;

template < class T >
class BinarySearchTree// : public Drawable
{

   private:
      TreeNode<T>* root;
      int sze;
      void destroyItem(TreeNode<T>* tNode);
      void destroy();

      TreeNode<T>* insertItem(TreeNode<T>* tNode, T item);
      TreeNode<T>* removeItem(TreeNode<T>* tNode, string sk);
      TreeNode<T>* removeNode(TreeNode<T>* tNode);
      TreeNode<T>* removeLeftMost(TreeNode<T>* tNode);
      T findLeftMost(TreeNode<T>* tNode);

      TreeNode<T>* getRootNode();
      void setRootNode(TreeNode<T>* tNode);
      int getHeight(TreeNode<T>* tNode);
      bool isBalanced(TreeNode<T>* tNode);


   public:
      BinarySearchTree();
      ~BinarySearchTree();

      bool isEmpty();
      void makeEmpty();

      T retrieve(string search_keys);
      void insert(T item);
      void remove(string search_keys);

      BinaryTreeIterator<T>* iterator();
      T getRootItem();
      int getHeight();
      bool isBalanced();

      T* toArray();
      static T* treeSort(T items, int num_itemss);

//      virtual void draw(wxDC& dc, int width, int height);
//     virtual void mouseClicked(int x, int y);
};

template < class T >
void BinarySearchTree<T>::remove(string sk)
{
   //DO THIS
	root = removeItem(root, sk);  //removes

}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeItem(TreeNode<T>* tNode, string sk)
{
   //DO THIS
	if(tNode == NULL) return tNode;
	
	T item = tNode->getItem();
	
	int compare = (*compare_keys)(sk, item);
	
	if (compare > 0)
	{
		TreeNode<T>* sub = removeItem(tNode->getRight(), sk);
		tNode->setRight(sub);
		return tNode;
	}
	else if (compare < 0)
	{
		TreeNode<T>* sub = removeItem(tNode->getLeft(), sk);
		tNode->setLeft(sub);
		return tNode;
	}
	else
	{
		sze--;
		return removeNode(tNode);
	}


}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeNode(TreeNode<T>* tNode)
{

   if (tNode->getLeft() == NULL && tNode->getRight() == NULL)
   {
      delete tNode;
      return NULL;
   }
   else if (tNode->getLeft() == NULL)
   {
      TreeNode<T>* temp = tNode->getRight();
      delete tNode;
      return temp;
   }
   else if (tNode->getRight() == NULL)
   {
      TreeNode<T>* temp = tNode->getLeft();
      delete tNode;
      return temp;
   }
   else 
   {
      //DO THIS
		TreeNode<T>* tempN = tNode->getRight();
		T temps = findLeftMost(tempN);
		tNode->setItem(temps);
		TreeNode<T>* sub = removeLeftMost(tNode->getRight());
		tNode->setRight(sub);
		return tNode;
   }
}

template < class T >
T BinarySearchTree<T>::findLeftMost(TreeNode<T>* tNode)
{
   //DO THIS (use a while loop)

   while(tNode->getLeft())
   {
	   tNode = tNode->getLeft();
   }
   T item = tNode->getItem();
   return item;
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::removeLeftMost(TreeNode<T>* tNode)
{
   //DO THIS (recursion)

	if(!tNode->getLeft())
	{
		TreeNode<T>* right = tNode->getRight();
		delete tNode;
		return right;
	}
	TreeNode<T>* sub = removeLeftMost(tNode->getLeft());
	tNode->setLeft(sub);
	return tNode;
}

template < class T >
T* BinarySearchTree<T>::toArray()
{
   //DO THIS

   T* to_array = new T[sze];
   int counter = 0;
   BinaryTreeIterator<T>* iter = iterator();
   iter->setInorder();
   while(iter->hasNext())
   {
	   to_array[counter] = iter->next();
   }
   delete iter;
   return to_array;

}

template < class T >
T BinarySearchTree<T>::treeSort(T items)
{
   //DO THIS

	BinarySearchTree<T>* bSearchTree = new BinarySearchTree<T>(comp_items, comp_keys);
	
	for(int i = 0; i < num_itemss; i++)
	{
		bSearchTree->insert(items[i]);
	}
	
	T* sorted_tree = bSearchTree->toArray();
	delete bSearchTree;
	return sorted_tree;

}

template < class T >
int BinarySearchTree<T>::getHeight()
{
   return getHeight(getRootNode());
}

template < class T >
int BinarySearchTree<T>::getHeight(TreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
       return 0;
   }
   else
   {
       int left = getHeight(tNode->getLeft());
       int right = getHeight(tNode->getRight());

       if (left >= right)
       {
           return left + 1;
       }
       else
       {
          return right + 1;
       }
   }
}

template < class T >
bool BinarySearchTree<T>::isBalanced()
{
    bool bal = isBalanced(root);
    return bal;
}

template < class T >
bool BinarySearchTree<T>::isBalanced(TreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
       return true;
   }

   TreeNode<T>* left = tNode->getLeft();
   TreeNode<T>* right = tNode->getRight();

   bool left_bal = isBalanced(left);
   if (left_bal == false)
   {
      return false;
   }

   bool right_bal = isBalanced(right);
   if (right_bal == false)
   {
      return false;
   }

   int lh = getHeight(left);
   int rh = getHeight(right);
   
   if (abs(lh - rh) > 1)
   {
      return false;
   }

   return true;
}

template < class T >
BinarySearchTree<T>::BinarySearchTree()
{
   root = NULL;
   sze = 0;

   compare_items = comp_items;
   compare_keys = comp_keys;
}

template < class T >
BinarySearchTree<T>::~BinarySearchTree()
{
   destroy();
}

template < class T >
void BinarySearchTree<T>::destroy()
{
   destroyItem(root);
}

template < class T >
void BinarySearchTree<T>::destroyItem(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
bool BinarySearchTree<T>::isEmpty()
{
   return sze == 0;
}

template < class T >
void BinarySearchTree<T>::makeEmpty()
{
   destroy();
   root == NULL;
   sze = 0;
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::getRootNode()
{
   return root;
}

template < class T >
void BinarySearchTree<T>::setRootNode(TreeNode<T>* tNode)
{  
   root = tNode;
}

template < class T >
T BinarySearchTree<T>::getRootItem()
{
   T rootItem = root->getItem();
   return rootItem;
}

template < class T >
void BinarySearchTree<T>::insert(T item)
{
   root = insertItem(root, item);
}

template < class T >
T BinarySearchTree<T>::retrieve(string sk)
{
   TreeNode<T>* tNode = getRootNode();

   while (tNode != NULL)
   {
      T node_items = tNode->getItem();
      int comp = sk.compare(node_items);

      if (comp == 0)
      {
         //no duplicate search keys allowed, so do nothing
         return node_items;
      }
      else if (comp < 0)
      {
         tNode = tNode->getLeft();
      }
      else
      {
         tNode = tNode->getRight();
      }
   }

   return NULL; //item is not in the tree
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::insertItem(TreeNode<T>* tNode, T item)
{
   TreeNode<T>* subtree;
   if (tNode == NULL)
   { 
      sze++;
      return new TreeNode<T>(item);
   }

   T node_items = tNode->getItem();
   int comp = item.compare(node_items);

   if (comp == 0)
   {
      //no duplicate search keys allowed, so do nothing
      return tNode;
   }
   else if (comp < 0)
   {
      subtree = insertItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);
   }
   else
   {
      subtree = insertItem(tNode->getRight(), item);
      tNode->setRight(subtree);
   }
   
   return tNode;
}

template < class T >
BinaryTreeIterator<T>* BinarySearchTree<T>::iterator()
{
   return new BinaryTreeIterator<T>(root);
}

#endif
