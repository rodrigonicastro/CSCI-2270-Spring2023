#include "LinkedList.hpp"

using namespace std;

/*******************************
Mandatory: Silver Problem - Implement the insert and search functions
********************************/

// Search for a specified key and return a pointer to that node
//MANDATORY_TODO: complete this function
// Given the key this function will find the node where the key is present
// If found it will return the node, else NULL
Node* LinkedList::searchList(int key) {
    Node* ptr = head;

    while(head != 0){
      if(ptr->key == key){
        break;
      }

      else{
        ptr = ptr->next;
      }
    }

    return ptr;
}


// Add a new node to the list
//MANDATORY_TODO: complete this function
// This function will add a node with newKey after the prev node in the linked list
// if prev is null insertion is to be made at head
void LinkedList::insert(Node* prev, int newKey){
    Node* newNode = new Node;
    newNode->key = newKey;

    // cout << "head: " << head << endl;
    // if(head != 0) cout << "head->key: " << head->key << endl << "head->next: " << head->next << endl;

  //Check if head is Null i.e list is empty
  if(head == NULL){
    head = newNode;
  }

  // if list is not empty, look for prev and append our node there
  else if(prev == NULL)
  {
    newNode->next = head;
    head = newNode;
  }
  //general insertion
  else{
    prev->next = newNode;
  }
}


/*******************************
Optional: Gold Problem - Implement the swapFirstAndLast function
********************************/

// Swap the first and last nodes (don't just swap the values). Swap the Nodes
bool LinkedList::swapFirstAndLast()
{
    bool isSwapped = false;

    return isSwapped;
}

// Print the keys in your list
void LinkedList::printList(){
  Node* temp = head;

  while(temp->next != NULL){
    cout<< temp->key <<" -> ";
    temp = temp->next;
  }

  cout<<temp->key<<endl;
}
