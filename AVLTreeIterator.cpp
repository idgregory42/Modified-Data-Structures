#if !defined (NULL)
#define NULL 0
#endif

#include "AVLTreeIterator.h"
using DataLib::AVLTreeIterator;

template < class T >
AVLTreeIterator<T>::AVLTreeIterator(AVLTreeNode<T>* root)
{
   q = new queue<T>();
   this->root = root;
}

template < class T >
AVLTreeIterator<T>::~AVLTreeIterator()
{
   delete q;
}

template < class T >
bool AVLTreeIterator<T>::hasNext()
{
   return (!q->empty());
}

template < class T >
T AVLTreeIterator<T>::next()
{
   if (hasNext())
   {
      return q->pop();
   }
}

template < class T >
void AVLTreeIterator<T>::setInorder()
{
   dequeueAll();
   inorder(root);
}

template < class T >
void AVLTreeIterator<T>::inorder(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      inorder(tNode->getLeft());
      q->push(tNode->getItem());
      inorder(tNode->getRight());
   }
}

template < class T >
void AVLTreeIterator<T>::setPreorder()
{
   dequeueAll();
   preorder(root);
}

template < class T >
void AVLTreeIterator<T>::preorder(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      q->push(tNode->getItem());
      preorder(tNode->getLeft());
      preorder(tNode->getRight());
   }
}

template < class T >
void AVLTreeIterator<T>::setPostorder()
{
   dequeueAll();
   postorder(root);
}

template < class T >
void AVLTreeIterator<T>::postorder(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      postorder(tNode->getLeft());
      postorder(tNode->getRight());
      q->push(tNode->getItem());
   }
}

template < class T >
void AVLTreeIterator<T>::dequeueAll()
{
	while(!q->empty())
	{
		q->pop();
	}
}