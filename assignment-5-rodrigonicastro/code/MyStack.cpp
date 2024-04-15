#include <iostream>
#include <cstdlib>
#include <iostream>
#include "MyStack.hpp"

using namespace std;

MyStack::MyStack()
{
	head = NULL;
}

MyStack::~MyStack()
{
	while(head != 0) pop();
}

bool MyStack::isEmpty()
{
	if(head == 0) return true;
		
	else return false;
}

void MyStack::push(int val)
{
	Node* newNode = new Node;
	newNode->val = val;
	newNode->next = NULL;

	if(isEmpty()) head = newNode;

	else{
		newNode->next = head;
		head = newNode;
	}
}

void MyStack::pop()
{   
	if(head == 0) cout << "Stack empty, cannot pop an item!" << endl;

	else{
		Node* temp = head;

		head = head->next;

		delete temp;
	}
}

Node* MyStack::peek()
{
	if(head == 0){
		cout << "Stack empty, cannot peek!" << endl;
		return nullptr;
	}

	else return head;
}
