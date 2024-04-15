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

void BookCollection::addBook(string bookName, string author, double rating) {
    Book* temp = root;
    Book* newBook = new Book(bookName, author, rating);

    if(root != nullptr){
        while(temp != nullptr){
            if(bookName > temp->bookName){
                if(temp->right == NULL){
                    temp->right = newBook;
                    return;
                }

                else temp = temp->right;
            } 
            else{
                if(temp->left == NULL){
                    temp->left = newBook;
                    return;
                }

                else temp = temp->left;
            }
            
        }

        temp = newBook;
    }

    else root = newBook;
}

void BookCollection::showBookCollection() {
    if(root != nullptr) _showCollectionHelper(root);

    else cout << "Collection is empty." << endl;

}

void BookCollection::_showCollectionHelper(Book* T){
    if(T != nullptr){
        if(T->left != nullptr){
            _showCollectionHelper(T->left);
        }

        cout << "BOOK: " << T->bookName << " BY: " << T->author << " RATING: " << T->rating << endl;

        if(T->right != nullptr){
            _showCollectionHelper(T->right);
        }      
    }

    else cout << "Collection is empty." << endl;
}

void BookCollection::showBook(string bookName) {
    bool foundBook = false;

    Book* temp = root;

    while(temp != nullptr){
        if(bookName > temp->bookName) temp = temp->right;

        else if(bookName < temp->bookName) temp = temp->left;

        else{
            foundBook = true;
            break;
        }
    }

    if(foundBook == true){
        cout << "Book:" << endl;
        cout << "==================" << endl;
        cout << "Name :" << temp->bookName << endl;
        cout << "Author :" << temp->author << endl;
        cout << "Rating :" << temp->rating << endl;
    }

    else cout << "Book not found." << endl;
}

void BookCollection::showBooksByAuthor(string author) {
    cout << "Books By: " << author << endl;
    _showBooksByAuthorHelper(root, author);
}

void BookCollection::_showBooksByAuthorHelper(Book* T, string author){
    if(T != nullptr){
        if(T->left != nullptr){
            _showBooksByAuthorHelper(T->left, author);
        }

        if(author == T->author) cout << T->bookName << " RATING: " << T->rating << endl;

        if(T->right != nullptr){
            _showBooksByAuthorHelper(T->right, author);
        }      
    }
}

void BookCollection::showHighestRatedBooks() {
    if(root != nullptr){
        double highestRating = _findHighestRatingHelper(root, 0);
        cout << "Highest Rating: " << highestRating << endl;
        _printHighestRating(root, highestRating);
    }

    else cout << "Collection is empty." << endl;
}

double BookCollection::_findHighestRatingHelper(Book* T, double currentHighest){
    if(T->left != nullptr){
        currentHighest = _findHighestRatingHelper(T->left, currentHighest);
    }

    if(T->rating > currentHighest) currentHighest = T->rating;

    if(T->right != nullptr){
        currentHighest = _findHighestRatingHelper(T->right, currentHighest);
    }

    return currentHighest;
}

void BookCollection::_printHighestRating(Book* T, double highestRating){
    if(T != nullptr){
        if(T->left != nullptr){
            _printHighestRating(T->left, highestRating);
        }

        if(highestRating == T->rating) cout << T->bookName << " BY: " << T->author << endl;

        if(T->right != nullptr){
            _printHighestRating(T->right, highestRating);
        }      
    }

    else cout << "Collection is empty." << endl;
}

int BookCollection::getHeightOfBookCollection() {
   return _getHeightHelper(root, 0);
}

int BookCollection::_getHeightHelper(Book* T, int counter) {
     if(T != nullptr){
        int leftHeight = _getHeightHelper(T->left, 0) + 1;
        int rightHeight = _getHeightHelper(T->right, 0) + 1;

        if(leftHeight >= rightHeight) return leftHeight;

        else return rightHeight;
    }

    else return 0;
}
