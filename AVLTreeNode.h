#if !defined (AVLTREENODE_H)
#define AVLTREENODE_H

#include "AVL.h"
using namespace DataLib;

namespace DataLib
{
template < class T >
class AVLTreeNode
{
   private:
      AVL balanceFactor;

      AVLTreeNode<T>* left;
      AVLTreeNode<T>* right;

      T item;

   public:
   
      AVLTreeNode(T item);
      ~AVLTreeNode();

      AVLTreeNode<T>* getLeft();
      AVLTreeNode<T>* getRight();
      T getItem();

      void setLeft(AVLTreeNode<T>* l);
      void setRight(AVLTreeNode<T>* r);
      void setItem(T data);

      void setBalanceFactor(AVL bf);
      AVL getBalanceFactor();

      void insertLeft();
      void insertRight();

      void removeLeft();
      void removeRight();

};
}

#endif
