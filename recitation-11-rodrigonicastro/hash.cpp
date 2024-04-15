// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

node* HashTable::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(int key)
{
    return (key % tableSize);
}

// TODO Complete this function
//function to search
node* HashTable::searchItem(int key)
{
    //Compute the index by using the hash function
    int index = hashFunction(key);

    //TODO: Search the list at that specific index and return the node if found
    if(table[index] == nullptr) return nullptr;

    node* curr = table[index];

    while(curr != nullptr){
        if(curr->key == key) return curr;
        curr = curr->next;
    }
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(int key)
{
    if(!searchItem(key))
    {
        // TODO :
        // Use the hash function on the key to get the index/slot,
        // create a new node with the key and insert it in this slot's list
        node* head = table[hashFunction(key)];
        node* newNode = createNode(key, nullptr);

        newNode->next = head;
        table[hashFunction(key)] = newNode;

        return true;
     }
    else{
        cout<<"duplicate entry: "<<key<<endl;
        return false;
    }

}

//TODO Complete this function
// function to display hash table
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";

        //TODO
        if (table[i] != 0) cout << "[" << i << "] -> Key: " << table[i]->key << " (#" << hashFunction(table[i]->key)<< ")" << endl; 
	    
        else cout << "[" << i << "] -> Empty" << endl;
    }

 }
