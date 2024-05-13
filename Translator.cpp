/*
 * Translator.cpp
 * 
 * Description: Instantiates and uses object from dictionary class.
 *              Translates English words into French words (from myDataFile.txt)
 *              
 *              
 * Author: Kyle Wong
 * Date of last modification: March 15th, 2024
 */

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "BST.h"
#include "WordPair.h"
#include "ElementAlreadyExistsException.h"
#include "ElementDoesNotExistException.h"
#include "EmptyDataCollectionException.h"
#include "UnableToInsertException.h"
#include "Dictionary.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::nothrow;

void display(WordPair& anElement) {
   cout << anElement;
} 

int main(int argc, char *argv[]) {

    Dictionary * testing = new(nothrow) Dictionary();

    if (testing != nullptr) {
      
        string aLine = "";
        string aWord = "";
        string englishW = "";
        string translationW = "";
        string filename = "myDataFile.txt";
        string delimiter = ":";
        size_t pos = 0;
        WordPair translated;
	 
        // Expecting at least a filename on the command line.
        if ( ( argc > 1 ) ) {

            filename = argv[1];
            ifstream myfile(filename);

            if (myfile.is_open()) {

                cout << "Reading from a file:" << endl;  // For debugging purposes

                while ( getline (myfile,aLine) ) {

                    pos = aLine.find(delimiter);    
                    englishW = aLine.substr(0, pos);
                    aLine.erase(0, pos + delimiter.length());
                    translationW = aLine;
                    WordPair aWordPair(englishW, translationW);

                    // BEGINNING OF TESTING USING CATCH/TRY

                    // testing put function...
                    try{

                        testing->put(aWordPair);

                    }
                    catch(ElementAlreadyExistsException& element){

                        cout << "Element already exists, put failed" << endl; 

                    }
                    catch(ElementDoesNotExistException& element){

                        cout << "Element does not exist, put failed" << endl;

                    } 
                }

                myfile.close();

            // testing get function...
            // if user enters ./translate myDataFile.txt, run translator 
            if(argc == 2 && strcmp(argv[0], "./translate") == 0 && strcmp(argv[1], "myDataFile.txt") == 0){
    
                // get aWord from user...
                cout << "Please enter word to be translated: ";

                while(getline(cin, aWord)){
                    
                    // insert aWord into aWordPair
                    WordPair aWordPair(aWord);

                    try{

                        WordPair retrievedWord = testing->get(aWordPair);
                        cout << retrievedWord;

                    }
                    catch(ElementDoesNotExistException& element){

                        cout << "***Not Found!***" << endl;

                    }
                    catch(EmptyDataCollectionException& element){

                        cout << "Data collection is empty" << endl;

                    }

                    cout << "Please enter another word to be translated: ";
                    
                } 
                
            }
            // testing displayContent...
            // if user enters ./translate myDataFile.txt display  
            else if(argc == 3 && strcmp(argv[0], "./translate") == 0 && strcmp(argv[1], "myDataFile.txt") == 0 && strcmp(argv[2], "display") == 0){

                try{

                    // call displayContent to display testing, throws exception if empty
                    testing->displayContent(display);

                }
                catch(EmptyDataCollectionException& element){

                    throw EmptyDataCollectionException();

                }

            }

            }
	        else{

                cout << "Unable to open file" << endl;

            } 
        }
        else{

            cout << "Missing the data filename!" << endl;

        }  
    }
    else{

        cout << "new failed!" << endl;

    }  

    delete testing;
    testing = nullptr;
      	
    return 0;

}