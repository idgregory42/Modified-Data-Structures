#if !defined (NULL)
#define NULL 0
#endif

#if !defined (AVLTREE_H)
#define AVLTREE_H

#include "AVLTreeIterator.h"
#include "2111/GUI/Drawable.h"
#include "2111/GUI/Line.h"
#include "Avl.h"

#include <string>
using namespace std;

template < class T >
class AVLTree : public Drawable
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

	  virtual void drawRec(AVLTreeNode<T>* tNode, wxDC& dc, Line* line, int x_parent, int x_curr, int y_curr);
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
	  void draw(wxDC&  dc, int width, int height);
      void mouseClicked(int x, int y);
};

template < class T >
AVLTree<T>::AVLTree(bool min_max, bool allow_dupes, bool dupes_on_left)
{
   root = NULL;
   sze = 0;


   allow_duplicates = allow_dupes;
   duplicates_on_left = dupes_on_left;
   min_or_max = min_max;
}

template < class T >
AVLTree<T>::AVLTree()
{
   root = NULL;
   sze = 0;

   allow_duplicates = false;
   duplicates_on_left = true;
   min_or_max = true;
}

template < class T >
AVLTree<T>::~AVLTree()
{
   destroy();
}

template < class T >
T AVLTree<T>::remove()
{
   T item = NULL;
   if (root == NULL) return item;

   AVLTreeNode<T>* subtree;
   sze--;

   if (min_or_max)
   {
      item = findLeftMost(root);
      subtree = removeLeftMost(root);
      root = subtree;
   }

   else
   {
      item = findRightMost(root);
      subtree = removeRightMost(root);
      root = subtree;
   }

   avlFlag = false;
   return item;
}

template < class T >
T AVLTree<T>::findLeftMost(AVLTreeNode<T>* tNode)
{
   while (tNode->getLeft() != NULL)
   {
      tNode = tNode->getLeft();
   }

   return tNode->getItem();
}

template < class T >
T AVLTree<T>::findRightMost(AVLTreeNode<T>* tNode)
{
   while (tNode->getRight() != NULL)
   {
      tNode = tNode->getRight();
   }

   return tNode->getItem();
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeLeftMost(AVLTreeNode<T>* tNode) 
{
   AVLTreeNode<T>* subtree;

   if (tNode->getLeft() == NULL) 
   {
      avlFlag = true;
      subtree = tNode->getRight();
      delete tNode;
      return subtree;
   }
   else 
   {
      subtree = removeLeftMost(tNode->getLeft());
      tNode->setLeft(subtree);
      if (avlFlag)
      {
         tNode = avlFixRemoveLeft(tNode);
      }
      return tNode;
   }  
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeRightMost(AVLTreeNode<T>* tNode) 
{
   AVLTreeNode<T>* subtree;

   if (tNode->getRight() == NULL) 
   {
      avlFlag = true;
      subtree = tNode->getLeft();
      delete tNode;
      return subtree;
   }
   else 
   {
      subtree = removeRightMost(tNode->getRight());
      tNode->setRight(subtree);
      if (avlFlag)
      {
         tNode = avlFixRemoveRight(tNode);
      }
      return tNode;
   }  
}

template < class T >
void AVLTree<T>::destroy()
{
   destroyItem(root);
}

template < class T >
void AVLTree<T>::destroyItem(AVLTreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
bool AVLTree<T>::isEmpty()
{
   return (sze == 0);
}

template < class T >
int AVLTree<T>::size()
{
   return sze;
}

template < class T >
void AVLTree<T>::makeEmpty()
{
   destroy();
   root == NULL;
   sze = 0;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::getRootNode()
{
   return root;
}

template < class T >
void AVLTree<T>::setRootNode(AVLTreeNode<T>* tNode)
{  
   root = tNode;
}

template < class T >
T AVLTree<T>::getRootItem()
{
   T root_item = root->getItem();
   return root_item;
}

template < class T >
AVLTreeIterator<T>* AVLTree<T>::iterator()
{
   return new AVLTreeIterator<T>(root);
}

template < class T >
T AVLTree<T>::retrieve(string sk)
{
   AVLTreeNode<T>* tNode = getRootNode();

   while (tNode != NULL)
   {
      T node_item = tNode->getItem();
      int comp = sk.compare(node_item);
      if (comp == 0)
      {
         return node_item;
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

   return NULL;
} 

template < class T >
void AVLTree<T>::insert(T item)
{
   root = insertItem(root, item);
   avlFlag = false;
} 

template < class T >
AVLTreeNode<T>* AVLTree<T>::insertItem(AVLTreeNode<T>* tNode, T item) 
{
   if (tNode == NULL) 
   {
      tNode = new AVLTreeNode<T>(item);
      tNode->setBalanceFactor(BALANCED);
      avlFlag = true;
      sze++;
      return tNode;
   } 

   AVLTreeNode<T>* subtree;
   T node_item = tNode->getItem();
   int comp = item.compare(node_item);

   if (comp == 0)
   {

      if (allow_duplicates)
      {
         if (duplicates_on_left)
         {
            subtree = insertItem(tNode->getLeft(), item);
            tNode->setLeft(subtree);

            if (avlFlag)
            {
               tNode = avlFixAddLeft(tNode);
            }
         }
         else
         {
            subtree = insertItem(tNode->getRight(), item);
            tNode->setRight(subtree);

            if (avlFlag)
            {
               tNode = avlFixAddRight(tNode);
            }
         }
      }


      else
      {
         return tNode;
      }
   }
   else if (comp < 0) 
   {
      subtree = insertItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);


      if (avlFlag)
      {
         tNode = avlFixAddLeft(tNode);
      }
   }
   else 
   { 
      subtree = insertItem(tNode->getRight(), item);
      tNode->setRight(subtree);

      if (avlFlag)
      {
         tNode = avlFixAddRight(tNode);
      }
   } 
   return tNode;
} 

template < class T >
void AVLTree<T>::remove(string sk)
{
   root = removeItem(root, sk);
   avlFlag = false;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeItem(AVLTreeNode<T>* tNode, string sk) 
{
   AVLTreeNode<T>* subtree;
   if (tNode == NULL) 
   {
      return tNode;
   }

   T node_item = tNode->getItem();

   int comp = sk.compare(node_item);

   if (comp == 0) 
   {
      avlFlag = true;
      tNode = removeNode(tNode);
      sze--;
   }
   else if (comp < 0) 
   {
      subtree = removeItem(tNode->getLeft(), sk);
      tNode->setLeft(subtree);
      if (avlFlag)
      {
         tNode = avlFixRemoveLeft(tNode);
      }
   }
   else 
   { 
      subtree = removeItem(tNode->getRight(), sk);
      tNode->setRight(subtree);
      if (avlFlag)
      {
         tNode = avlFixRemoveRight(tNode);
      }
   }  

   return tNode;
} 

template < class T >
AVLTreeNode<T>* AVLTree<T>::removeNode(AVLTreeNode<T>* tNode) 
{
   T replacement_item;

   if ((tNode->getLeft() == NULL) && (tNode->getRight() == NULL)) 
   {
      delete tNode;
      return NULL;
   }  
   else if (tNode->getLeft() == NULL) 
   {
      AVLTreeNode<T>* temp = tNode->getRight();
      delete tNode;
      return temp;
   } 
   else if (tNode->getRight() == NULL) 
   {
      AVLTreeNode<T>* temp = tNode->getLeft();
      delete tNode;
      return temp;
   }  
   else 
   {
      replacement_item = findLeftMost(tNode->getRight());
      tNode->setItem(replacement_item);
      tNode->setRight(removeLeftMost(tNode->getRight()));
      if (avlFlag)
      {
         tNode = avlFixRemoveRight(tNode);
      }
      return tNode;
   }  
}

template < class T >
bool AVLTree<T>::isBalanced()
{
    int bal = isBalanced(getRootNode());
    if (bal == -1)
    {
       return false;
    }
    return true;
}

template < class T >
int AVLTree<T>::isBalanced(AVLTreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
       return 0;
   }

   int balance = -1;
   AVLTreeNode<T>* left = tNode->getLeft();
   AVLTreeNode<T>* right = tNode->getRight();

   int left_height = isBalanced(left);
   int right_height = isBalanced(right);

   if (left_height != -1  &&  right_height != -1)
   {
       int bal = left_height - right_height;
       if (bal < 0) bal = bal * -1;
       if (bal <= 1)
       {
           if (left_height >= right_height)
           {
               balance = left_height + 1;
           }
           else
           {
               balance = right_height + 1;
           }
       }
   }
   return balance;
}

template < class T >
int AVLTree<T>::getHeight()
{
   int height = getHeight(root);
   return height;
}

template < class T >
int AVLTree<T>::getHeight(AVLTreeNode<T>* tNode)
{
   int height;
   int right_height;

   if (tNode == NULL)
   {
       return 0;
   }
   else
   {
       height = getHeight(tNode->getLeft());
       right_height = getHeight(tNode->getRight());

       if (right_height > height)
       {
           height = right_height;
       }

       return height + 1;
   }
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* right = tNode->getRight();
   AVLTreeNode<T>* rightleft = right->getLeft();

   tNode->setRight(rightleft);
   right->setLeft(tNode);

   return right;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* left = tNode->getLeft();
   AVLTreeNode<T>* leftright = left->getRight();

   tNode->setLeft(leftright);
   left->setRight(tNode);

   return left;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* left = tNode->getLeft();
   AVLTreeNode<T>* temp = rotateLeft(left);
   tNode->setLeft(temp);
   temp = rotateRight(tNode);
   return temp;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode)
{
   AVLTreeNode<T>* right = tNode->getRight();
   AVLTreeNode<T>* temp = rotateRight(right);
   tNode->setRight(temp);
   temp = rotateLeft(tNode);
   return temp;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left)
{
   AVLTreeNode<T>* leftRight = left->getRight();
   AVL LRBF = leftRight->getBalanceFactor();
   leftRight->setBalanceFactor(BALANCED);

   if (LRBF == RIGHT_HEAVY)
   {
      left->setBalanceFactor(LEFT_HEAVY);
   }
   else if (LRBF == LEFT_HEAVY)
   {
      tNode->setBalanceFactor(RIGHT_HEAVY);    
   }

   tNode = DLR(tNode);
   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right)
{
   AVLTreeNode<T>* rightLeft = right->getLeft();
   AVL RLBF = rightLeft->getBalanceFactor();
   rightLeft->setBalanceFactor(BALANCED);

   if (RLBF == RIGHT_HEAVY)
   {
      tNode->setBalanceFactor(LEFT_HEAVY);
   }
   else if (RLBF == LEFT_HEAVY)
   {
      right->setBalanceFactor(RIGHT_HEAVY);
   }

   tNode = DRL(tNode);
   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddLeft(AVLTreeNode<T>* tNode)
{
   tNode->insertLeft();
   AVL factor = tNode->getBalanceFactor();

   if (factor == BALANCED)
   {
      avlFlag = false;
   }
   else if (factor == LEFT_UNBALANCED)
   {
      AVLTreeNode<T>* left = tNode->getLeft();
      AVL LBF = left->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      left->setBalanceFactor(BALANCED);

      if (LBF == RIGHT_HEAVY)
      {
         tNode = DLR(tNode, left);
      }
      else 
      {
         tNode = rotateRight(tNode);
      }

      avlFlag = false;
   }
  
   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
   tNode->insertRight();
   AVL factor = tNode->getBalanceFactor();

   if (factor == BALANCED)
   {
      avlFlag = false;
   }
   else if (factor == RIGHT_UNBALANCED)
   {
      AVLTreeNode<T>* right = tNode->getRight();
      AVL RBF = right->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      right->setBalanceFactor(BALANCED);

      if (RBF == LEFT_HEAVY)
      {
         tNode = DRL(tNode, right);
      }

      else 
      {
         tNode = rotateLeft(tNode);
      }

      avlFlag = false;
   }

   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixRemoveLeft(AVLTreeNode<T>* tNode)
{
   tNode->removeLeft();
   AVL factor = tNode->getBalanceFactor();

   if (factor == RIGHT_HEAVY)
   {
      avlFlag = false;
   }
   else if (factor == RIGHT_UNBALANCED)
   {
      AVLTreeNode<T>* right = tNode->getRight();
      AVL RBF = right->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      right->setBalanceFactor(BALANCED);

      if (RBF == BALANCED)
      {
         tNode->setBalanceFactor(RIGHT_HEAVY);
         right->setBalanceFactor(LEFT_HEAVY);
         tNode = rotateLeft(tNode);
         avlFlag = false;
      }
      else if (RBF == RIGHT_HEAVY)
      {
         tNode = rotateLeft(tNode);
      }
      else
      {
         tNode = DRL(tNode, right);
      }
   }

   return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixRemoveRight(AVLTreeNode<T>* tNode)
{
   tNode->removeRight();
   AVL factor = tNode->getBalanceFactor();

   if (factor == LEFT_HEAVY)
   {
      avlFlag = false;
   }
   else if (factor == LEFT_UNBALANCED)
   {
      AVLTreeNode<T>* left = tNode->getLeft();
      AVL LBF = left->getBalanceFactor();

      tNode->setBalanceFactor(BALANCED);
      left->setBalanceFactor(BALANCED);

      if (LBF == BALANCED)
      {
         tNode->setBalanceFactor(LEFT_HEAVY);
         left->setBalanceFactor(RIGHT_HEAVY);
         tNode = rotateRight(tNode);
         avlFlag = false;
      }
      else if (LBF == LEFT_HEAVY)
      {
         tNode = rotateRight(tNode);
      }
      else 
      {
         tNode = DLR(tNode, left);
      }
   }

   return tNode;
}

template < class T >
void AVLTree<T>::draw(wxDC&  dc, int width, int height)
{
   Line line(new Color(0, 0, 0), 5.0);
   drawRec(getRootNode(), dc, &line, width, width/2, 20);
}

template < class T >
void AVLTree<T>::drawRec(AVLTreeNode<T>* tNode, wxDC&  dc, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(dc, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), dc, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), dc, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(dc, x_curr, y_curr);
   }
}

template < class T >
void AVLTree<T>::mouseClicked(int x, int y) {}

#endif
