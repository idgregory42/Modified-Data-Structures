#if !defined (AVLTREEITERATOR_H)
#define AVLTREEITERATOR_H

#include "AVLTreeNode.h"
using DataLib::AVLTreeNode;

#include <queue>
using namespace std;

namespace DataLib
{
template < class T >
class AVLTreeIterator
{

   private:
      queue<T>* q;
      AVLTreeNode<T>* root;

      void inorder(AVLTreeNode<T>* tNode);
      void preorder(AVLTreeNode<T>* tNode);
      void postorder(AVLTreeNode<T>* tNode);

   public:
      ~AVLTreeIterator();
      AVLTreeIterator(AVLTreeNode<T>* root);

      bool hasNext();
      T next();

      void setInorder();
      void setPreorder();
      void setPostorder();
	  void dequeueAll();

};


}
#endif
