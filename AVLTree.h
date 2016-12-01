
#if !defined (AVLTREE_H)
#define AVLTREE_H

#include "AVLTreeIterator.h"
using DataLib::AVLTreeIterator;

#include "Avl.h"

#include <string>
using namespace std;

namespace DataLib
{
template < class T >
class AVLTree
{
   
   private:
      AVLTreeNode<T>* root;

      bool avlFlag;
	  int sze;
      bool allow_duplicates;
      bool duplicates_on_left;
      bool min_or_max;

      void setRootNode(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* getRootNode();
      int getHeight(AVLTreeNode<T>* tNode);
      int isBalanced(AVLTreeNode<T>* tNode);

      void destroyItem(AVLTreeNode<T>* tNode);
      void destroy();

      AVLTreeNode<T>* insertItem(AVLTreeNode<T>* tNode, T item);
      AVLTreeNode<T>* removeItem(AVLTreeNode<T>* tNode, string searchKey);
      AVLTreeNode<T>* removeNode(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* removeLeftMost(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* removeRightMost(AVLTreeNode<T>* tNode);
      T findLeftMost(AVLTreeNode<T>* tNode);
      T findRightMost(AVLTreeNode<T>* tNode);

      AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode);

      AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* avlFixAddRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* avlFixRemoveLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* avlFixRemoveRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left);
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right);


   public:
      AVLTree();
      AVLTree(bool min_or_max, bool allow_duplicates, bool duplicates_on_left);
      ~AVLTree();

      int size();
      void insert(T item);
      void remove(string sk);
      T remove();
      T retrieve(string sk);

      bool isEmpty();
      void makeEmpty();

      T getRootItem();
      AVLTreeIterator<T>* iterator();

      int getHeight();
      bool isBalanced();

};

}
#endif
