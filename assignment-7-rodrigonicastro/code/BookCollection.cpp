#include "BookCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

BookCollection::BookCollection() {
    root = nullptr;
}

BookCollection::~BookCollection() {
     _destructorHelper(root);
}

void BookCollection::_destructorHelper(Book* T){
    if(T != nullptr){
        if(T->right != nullptr) _destructorHelper(T->right);

        if(T->left != nullptr) _destructorHelper(T->left);
        
        delete T;
        T = nullptr;
    }
}


void BookCollection::removeBook(string bookName){
    _removeBookHelper(bookName, root);
}

void BookCollection::_removeBookHelper(string bookName, Book* &T){
    if(T == nullptr) cout << "Book not found!" << endl;
    else if(bookName < T->bookName) _removeBookHelper(bookName, T->left);
    else if(bookName > T->bookName) _removeBookHelper(bookName, T->right);

    else{
        if(T->right == nullptr && T->left == nullptr){
            delete T;
            T = 0;
        }

        else if(T->right == nullptr && T->left != nullptr){
            Book* child = T->left;
            delete T;
            T = child;
        }

        else if(T->right != nullptr && T->left == nullptr){
            Book* child = T->right;
            delete T;
            T = child;
        }

        else{
            Book* temp = _findMin(T->right);
            T->bookName = temp->bookName;
            T->rating = temp->rating;
            T->author = temp->author;

            _removeBookHelper(T->bookName, T->right);
        }
    }
}

void BookCollection::rotateLeftCollection(string bookName){
    Book* x = _searchBook(bookName, root);

    if(x == nullptr || x->right == nullptr) return;

    else if(x == root){
        Book* y = x->right;

        x->right = y->left;
        y->left = x;

        root = y;
    }

   else{
        Book* xp = _findParent(bookName, root); 
        Book* y = x->right;
        
        x->right = y->left;
        y->left = x;

        if(x == xp->right) xp->right = y;

        else xp->left = y;

   }
}

string BookCollection::closestParent(string book1, string book2) {
    string result;

    if(_searchBook(book1, root) == nullptr || _searchBook(book2, root) == nullptr){
        cout << "Book not found!" << endl;
        return "Error - wrong book name";
    }

    else{
        int size = getHeightOfBookCollection();

        string pathToBook1[size];
        int sizeOfPath1 = _findPath(book1, root, pathToBook1);
        
        string pathToBook2[size];
        int sizeOfPath2 = _findPath(book2, root, pathToBook2);
      
        if(sizeOfPath1 == 0 || sizeOfPath2 == 0) result = root->bookName;

        else{
            if(sizeOfPath1 > sizeOfPath2){
                for(int i = 0; i < sizeOfPath1; i++){
                    if(book2 == pathToBook1[i]) return book2;
                }
            }

            else{
                for(int i = 0; i < sizeOfPath2; i++){
                    if(book1 == pathToBook1[i]) return book1;
                }
            }

            for(int i = sizeOfPath1 - 1; i >= 0 ; i--){
                for(int j = sizeOfPath2 - 1; j >= 0; j--){
                    if(pathToBook1[i] == pathToBook2[j]) return pathToBook1[i];
                }
            }
        }
        return result;
    }
}

int BookCollection::_findPath(string bookName, Book* T, string path[]){
    Book* temp = T;
    int counter = 0;

    while(temp->bookName != bookName){
        if(bookName < temp->bookName){
            path[counter] = temp->bookName;
            counter++;
            temp = temp->left;
        }

        else{
            path[counter] = temp->bookName;
            counter++;
            temp = temp->right;
        }
    }

    return counter;
}

Book* BookCollection::_findParent(string bookName, Book* T){
    if(_searchBook(bookName, root) == nullptr) return nullptr;
    
    Book* temp = T;

    if(root->bookName == bookName) return nullptr;

    while(temp != 0){
        if(temp->right != nullptr){
            if(temp->right->bookName == bookName) return temp;
        }

        if(temp->left != nullptr){
            if(temp->left->bookName == bookName) return temp;
        }

        if(bookName < temp->bookName){
            temp = temp->left;
        }
        
        else temp = temp->right;
    }
    return temp;
}

Book* BookCollection::_searchBook(string bookName, Book* T){
    if(T == nullptr) return nullptr;

    else{
        Book* temp = T;
        bool foundBook = false;

        while(temp != nullptr){
            if(bookName < temp->bookName) temp = temp->left;

            else if(bookName > temp->bookName) temp = temp->right;

            else{
                foundBook = true;
                break;
            }
        }

        if(foundBook == true) return temp;

        else return nullptr;
    }
}

Book* BookCollection::_findMin(Book* T){
    if(T->left == nullptr) return T;

    else return _findMin(T->left);
}