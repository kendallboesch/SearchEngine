//
// Created by Akul Bavare on 4/11/2022.
//

#ifndef INC_22S_FINAL_PROJECT_KENDALL_AKUL_AVLTREE_H
#define INC_22S_FINAL_PROJECT_KENDALL_AKUL_AVLTREE_H
#include <iostream>
#include <variant>
#include <vector>
#include "AVLNode.h"

using namespace std;


template <class T>
class AVLTree{
private:
    AVLNode<T>* root;
public:

    AVLTree(): root(NULL){}
    AVLTree(const AVLTree<T> &rhs) : root(NULL) {*this = rhs;}
    ~AVLTree()
    {
        makeEmpty(root);
    }
    AVLNode<T>* getRoot()
    {
        return root;
    }
    //return the height of node t or -1 if nullptr
    int height(AVLNode<T> *t) {
        return t == nullptr ? -1 : t->height;
    }
    void insert(const T& x){
        insert(x, root);
    }
    bool insert(const T& x, T& f){
        return insert(x, f, root);
    }
    bool find( T& key )
    {
        return search(key, this->root);
    }
    vector<T> locate( T& key )
     {
        return at(key,this->root);
    }
    void makeEmpty(AVLNode<T>* t){
        if(t == nullptr)
        {
            return;
        }
        else
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
        }

    }
    void remove(const T &x){
        remove(x, root);
    }
    void  display(){
        inorder(root);
        cout << endl;
    }

    void inorder(AVLNode<T> *t){
        if(t == nullptr){
            return;
        }
        inorder(t->left);
        cout << t->key << " ";
        inorder(t->right);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree
     * Set the new root of the subtree.
     */
     void insert(const T& x, AVLNode<T>*& t)
     {
         if(t == nullptr)
         {
             t = new AVLNode<T>{x, nullptr, nullptr};
         }
         else if( x < t-> key)
         {
             insert(x, t ->left);
         }
         else if(t->key < x)
         {
             insert(x, t->right);
         }
         else
         {
             return;
         }

         balance(t);
     }

    void emptyTree()
    {

        auxEmptyTree(root->left);
        auxEmptyTree(root->right);
        delete root;

    }
    void auxEmptyTree(AVLNode<T>* n)
    {
        if(n->left != nullptr)
        {
            auxEmptyTree(n->left);
        }
        else
        {
            delete n->left;
        }
        if(n->right != nullptr)
        {
            auxEmptyTree(n->right);
        }
        else
        {
            delete n->right;
        }

    }
    bool insert(const T& x, T& f, AVLNode<T>*& t)
    {
        if(t == nullptr)
        {
            t = new AVLNode<T>{x, f, nullptr, nullptr};
            return true;
        }
        else if( x < t-> key)
        {
            insert(x, f, t ->left);
        }
        else if(t->key < x)
        {
            insert(x, f, t->right);
        }
        else
        {
            if (t->articles.at(t->articles.size()-1) != f)
                t->articles.push_back(f);
                return false;
        }
        balance(t);
    }

     bool search( T& x, AVLNode<T> *& t)
     {
         if(t == nullptr)
         {
             return false;
         }
      else if(t->key == x)
     {
         return true;
     }
     else if(t->key > x && t->left != nullptr)
     {
         return search( x,t->left);

     }
     else if( t->key < x && t->right != nullptr)
     {
        return search(x, t->right);

     }
     else
         {
         return false;
         }

     }

    vector<T> at(T &x, AVLNode<T> * t)
    {
         if (t == nullptr)
         {
           return {"NULL VECTOR"};
         }
         else if(x < t->key)
          {
             t =  t->left;
             return(at(x, t));
          }
         else if(t->key < x)
         {
             t = t->right;
             return(at(x, t));
         }
         else
         {
             return t-> articles;
         }
     }

      vector<T>& elementAt(AVLNode<T> *t)
      {
         if(t != nullptr && t != NULL)
         {
             return t->articles;
         }
         else
         {
            return variant_npos;
         }
     }


     //Assume t is balanced or within one of being balanced
     void balance(AVLNode<T> *& t){
         static const int ALLOWED_IMBALANCE = 1;
         if(t == nullptr){
             return;
         }
         if(height(t-> left) - height(t -> right)> ALLOWED_IMBALANCE){
             if(height(t -> left -> left) >= height(t -> left -> right)){
                 rotateWithLeftChild(t);//c1
             } else{
                 doubleWithLeftChild(t);//c2
             }
         }
         else if(height(t -> right) - height(t -> left) > ALLOWED_IMBALANCE){
                 if(height(t -> right -> right) >= height(t -> right -> left)){
                     rotateWithRightChild(t);//c4
                 }else{
                     doubleWithRightChild(t);//c3
                 }
             }

         t -> height = max(height(t -> left), height(t -> right)) + 1;
     }

     /**
      * Rotate binary tree node with left child.
      * For AVL trees, this is a single rotation for case 1.
      * Update heights, then set new root.
      */
      void rotateWithLeftChild(AVLNode<T> *& k2){
          AVLNode <T>*k1 = k2 -> left;
          k2 -> left = k1 -> right;
          k1 -> right = k2;
          k2 -> height = max(height(k2 -> left), height(k2 -> right)) +1;
          k1-> height = max(height(k1 -> left), k2 -> height) + 1;
          k2 = k1;
      }
      void rotateWithRightChild(AVLNode<T> *& k2){
          AVLNode<T> *k1 = k2 -> right;
          k2 -> right = k1 -> left;
          k1 -> left = k2;
          k2 -> height = max(height(k2 -> right), height(k2 -> left)) +1;
          k1->height = max(height(k1 -> right), k2->height) + 1;
          k2 = k1;
      }
     /**
2 * Double rotate binary tree node: first left child
3 * with its right child; then node k3 with new left child.
4 * For AVL trees, this is a double rotation for case 2.
5 * Update heights, then set new root.
6 */
     void doubleWithLeftChild( AVLNode<T> * & k3 )
     {
         rotateWithRightChild( k3->left );
         rotateWithLeftChild( k3 );
         }
    void doubleWithRightChild( AVLNode <T>* & k3 )
    {
        rotateWithLeftChild( k3->right );
        rotateWithRightChild( k3 );
    }
     /**
2 * Internal method to remove from a subtree.
3 * x is the item to remove.
4 * t is the node that roots the subtree.
5 * Set the new root of the subtree.
6 */
     void remove( const T & x, AVLNode<T> *&t)
    {
         if( t == nullptr ) {
             return; // Item not found; do nothing
         }
         if( x < t->key ) {
             remove(x, t->left);
         }
         else if( t->key < x ) {
             remove(x, t->right);
         }
         else if( t->left != nullptr && t->right != nullptr ) // Two children
             {
             t->key = findMin( t->right )->element;
             remove( t->key, t->right );
             }
         else
         {
             AVLNode <T>*oldNode = t;
             t = ( t->left != nullptr ) ? t->left : t->right;
             delete oldNode;
             }

         balance( t );
         }

         AVLNode<T>* findMin(AVLNode<T> *&t){
         if(t == nullptr){
             return nullptr;
         } else if(t->left == nullptr){
             return t;
         }
         else{
             return findMin(t->left);
         }
     }
     AVLNode<T>* findMax(AVLNode<T> *& t)
     {
         if(t == nullptr){
             return nullptr;
         } else if (t->right == nullptr){
             return t;
         }
         else{
             return findMax(t->right);
         }
     }
     bool isEmpty()
     {
         return this->root == nullptr;
     }



};


#endif //INC_22S_FINAL_PROJECT_KENDALL_AKUL_AVLTREE_H
