/*
 * BST.cpp
 * 
 * Description: Binary Search Tree data collection ADT class.
 *              Link-based implementation.
 *              Duplicated elements are not allowed.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Inspired from our textbook, Kyle Wong
 * Date of last modification: March 13th, 2024
 */
 
#include "BST.h"
#include "WordPair.h"
#include <iostream>

using std::cout;
using std::endl;
using std::nothrow;


// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one with which we will mark this assignment - 
// will not know about them since, in order to create it, we will have 
// used only the public method prototypes below.


/* Constructors and destructor */

   // Default constructor
   BST::BST() { }   

   // Description: Recurisively copies nodes
   // Postcondition: this method does not change the binary search tree
   BSTNode* BST::rcpyBST(BSTNode* aNode)
   {
      if (aNode)
      {
         BSTNode* cpyNode = new BSTNode();
         cpyNode->element = aNode->element;
         cpyNode->left = rcpyBST(aNode->left);
         cpyNode->right = rcpyBST(aNode->right);
         return cpyNode;
      }
      else
      {
         return nullptr;
      }
   }   

   // Copy constructor
   BST::BST(const BST & aBST) {

      BSTNode* aroot = aBST.root;
      elementCount = aBST.elementCount;
      root = rcpyBST(aroot);

   }

   // Description: Recurisively deletes nodes
   // Postcondition: all nodes of binary search tree are deleted
   void BST::rDestructor(BSTNode* aNode)      
   {

      if (aNode)
      {
         rDestructor(aNode->left);
         rDestructor(aNode->right);
         delete aNode;
      }

   }

   // Destructor 
   BST::~BST() {

      rDestructor(root);

   }                
   
   
/* Getters and setters */

   // Description: Returns the number of elements currently stored in the binary search tree.   
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(1)
   unsigned int BST::getElementCount() const {     

      return this->elementCount;
	 
   }
   

/* BST Operations */

   // Description: Inserts an element into the binary search tree.
   //              This is a wrapper method which calls the recursive insertR( ).
   // Precondition: "newElement" does not already exist in the binary search tree.
   // Exception: Throws the exception "UnableToInsertException" when newElement 
   //            cannot be inserted because the "new" operator failed. 
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the binary search tree.
   // Time efficiency: O(log2 n)   
   void BST::insert(WordPair & newElement) {
  
      // creates new node
      BSTNode* newNode = new BSTNode();

      // throws exception when 'new' operator fails
      if (!newNode)
      {
         throw UnableToInsertException("newElement cannot be inserted because 'new' operator failed.");
      }

      newNode->element = newElement;

      // if the tree is empty make this new node the root
      if (this->getElementCount() == 0)
      {

         this->root = newNode;
         // increments element count
         this->elementCount++;
         return;

      }

      // throws exception if value could not be inserted
      if (!insertR(newNode, this->root))
      {

         throw ElementAlreadyExistsException("The element you are trying to insert already exists in Binary Search Tree");

      }

      // if value was inserted increase element count
      else this->elementCount++;

   } 
   
   // Description: Recursive insertion into a binary search tree.
   //              Returns true when "anElement" has been successfully inserted into the 
   //              binary search tree. Otherwise, returns false.
   bool BST::insertR(BSTNode * newBSTNode, BSTNode * current) {  
    
      // returns false if value already exists
      if (current->element == newBSTNode->element)
      {
         return false;
      }
      // if the element is less than the node we are currently looking traverse the left side of the tree
      else if (current->element > newBSTNode->element)
      {
         // if the current element doesn't have anything in its left subtree insert then insert the new element there and return true
         if (!current->hasLeft())
         {
            current->left = newBSTNode;
            return true;
         }
         // traverses left subtree
         else insertR(newBSTNode, current->left);
      }
      // if the element is greater than the node we are currently looking at traverse the right side of the tree and return true
      else if (current->element < newBSTNode->element)
      {
         // if the current element doesn't have anything in its right subtree insert then insert the new element there
         if (!current->hasRight())
         {
            current->right = newBSTNode;
            return true;
         }
         // traverses right subtree
         else insertR(newBSTNode, current->right);
      }
      return true;
   }
   
   // Description: Retrieves "targetElement" from the binary search tree.
   //              This is a wrapper method which calls the recursive retrieveR( ).
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Exception: Propagates the exception "ElementDoesNotExistException" 
   //            thrown from the retrieveR(...)
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(log2 n)
   WordPair& BST::retrieve(WordPair & targetElement) const {
      
      if (elementCount == 0){

         throw EmptyDataCollectionException("Binary search tree is empty.");
      }  
	
      WordPair& translated = retrieveR(targetElement, root);
	 
      return translated;
   }

   // Description: Recursive retrieval from a binary search tree.
   // Exception: Throws the exception "ElementDoesNotExistException" 
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   WordPair& BST::retrieveR(WordPair & targetElement, BSTNode * current) const {

      // returns element if target element is found
      
      if (current->element == targetElement)
      {
         cout << targetElement;
         return current->element;
      }
      // traverses left subtree if targetElement is less than the current element
      else if (current->element > targetElement)
      {
         // check if the left subtree exists 
         if(current->hasLeft()){
            retrieveR(targetElement, current->left);
         }
         else 
         {
            throw ElementDoesNotExistException("Element could not be found in Binary Search Tree.");
            return targetElement;
         }
      }
      // traverses right subtree if targetElement is greater than the current element
      else if (current->element < targetElement)
      {
         // check if the right subtree exists 
         if(current->hasRight()){
            retrieveR(targetElement, current->right);
         }
         else
         {
            throw ElementDoesNotExistException("Element could not be found in Binary Search Tree.");
            return targetElement;
         }
      }
   } 
         
   
   // Description: Traverses the binary search tree in order.
   //              This is a wrapper method which calls the recursive traverseInOrderR( ).
   //              The action to be done on each element during the traverse is the function "visit".
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(n)     
   void BST::traverseInOrder(void visit(WordPair &)) const {
     
      if (elementCount == 0){

         throw EmptyDataCollectionException("Binary search tree is empty.");

      }  
   
     traverseInOrderR(visit, root);
     
     return;
   }

   // Description: Recursive in order traversal of a binary search tree.   
   // Postcondition: This method does not change the binary search tree. 
   void BST::traverseInOrderR(void visit(WordPair &), BSTNode* current) const { 
   
      if (current != nullptr)
      {
         // traverses left subtree
         traverseInOrderR(visit, current->left);

         // visits element
         visit(current->element);

         // traverses right subtree
         traverseInOrderR(visit, current->right);
      }

   }
