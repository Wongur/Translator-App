/*
 * Dictionary.cpp
 * 
 * Description: Dictonary data collection ADT class.
 *              BST-based implementation.
 *              Duplicated elements not allowed.
 *              
 * Author: Kyle Wong
 * Date of last modification: March 15th, 2024
 */

#include "Dictionary.h"
#include "Wordpair.h"
#include <iostream>

using std::cout;
using std::endl;
using std::nothrow;

// Default Constructor 
Dictionary::Dictionary(){}

// Destructor
Dictionary::~Dictionary(){

    delete keyValuePairs;
    keyValuePairs = nullptr;

}

// Name: getElementCount
// Description: Returns the number of elements currently stored in the binary search tree.   
// Postcondition: This method does not change the binary search tree.
// Time efficiency: O(1)
unsigned int Dictionary::getElementCount() const{

    return keyValuePairs->getElementCount();

}

// Name: put 
// Description: Puts "newElement" (association of key-value) into the Dictionary.
// Precondition: "newElement" does not already exist in the Dictionary.
//               This is to say: no duplication allowed.
// Exception: Throws the exception "UnableToInsertException" 
//            when newElement cannot be inserted in the Dictionary.  
// Exception: Throws the exception "ElementAlreadyExistsException" 
//            if "newElement" already exists in the Dictionary. 
void Dictionary::put(WordPair & newElement){

    try{

        // check if keyValuePairs is empty
        if(keyValuePairs == nullptr){

            // creating a new BST tree
            BST* newBST = new BST();

            // if new memory allocation was unsuccessful...
            if(newBST == nullptr){
                
                // throw unable to insert exception 
                throw UnableToInsertException();

            }

            // assign created new memory location to keyValuePairs
            keyValuePairs = newBST;

        }

        // call BST class' insert function to insert newElement into keyValuePairs, insert function throws exceptions if unsuccessful 
        keyValuePairs->insert(newElement);

    }
    // catching exception from BST's insert 
    catch(ElementAlreadyExistsException& element){

        // throw new exception for Dictionary class
        throw ElementAlreadyExistsException();        

    }
    // catching exception from BST's insert 
    catch(ElementDoesNotExistException& element){

        // throw new exception for Dictionary class 
        throw ElementDoesNotExistException();

    }

}

// Name: get
// Description: Gets "newElement" (i.e., the associated value of a given key) 
//              from the Dictionary.
// Precondition: Dictionary is not empty.
// Exception: Throws the exception ElementDoesNotExistException
//            if the key is not found in the Dictionary.
// Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
// Postcondition: This method does not change the Dictionary.
WordPair& Dictionary::get(WordPair & targetElement) const{

    try{

        // calling retrieve function from part 1, throws exception if empty or does not exist
        return keyValuePairs->retrieve(targetElement);

    }
    // catching the thrown exceptions from retrieve and retrieveR
    catch(ElementDoesNotExistException& element){

        throw ElementDoesNotExistException();

    }
    catch(EmptyDataCollectionException& element){

        throw EmptyDataCollectionException();

    }

}

// Name: displayContent
// Description: Prints the content of the Dictionary.
// Precondition: Dictionary is not empty.
// Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
// Postcondition: This method does not change the Dictionary.
void Dictionary::displayContent(void visit(WordPair &)) const{

    try{

        // calling traverse function from part 1, throws exception if empty
        keyValuePairs->traverseInOrder(visit);

    }
    // catching the thrown exception from traverse, throw exception for displayContent
    catch(EmptyDataCollectionException& element){

        throw EmptyDataCollectionException();

    }

}
