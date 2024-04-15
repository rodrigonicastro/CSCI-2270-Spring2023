#include "MyQueue.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

MyQueue::MyQueue(){
    queueFront = -1;
	queueEnd = -1;
}

bool MyQueue::isEmpty(){
	if(counter == 0) return true; 
    
	else return false;
}

bool MyQueue::isFull(){
	if(counter == SIZE) return true;
    
	else return false;
}

void MyQueue::enqueue(char ch){
	if(isEmpty()){
		queueEnd = (queueEnd + 1) % SIZE;
		queueFront = (queueFront + 1) % SIZE;
		queue[queueEnd] = ch;
		counter++;
		return;
	}
	
	else if(!isFull()){	
		queueEnd = (queueEnd + 1) % SIZE;
		queue[queueEnd] = ch;		
		counter++;
		return;
	}

	else cout << "Queue full, cannot add!" << endl;
}


void MyQueue::dequeue(){
	if(isEmpty()){
		cout << "Queue empty, cannot dequeue!" << endl;
		return;
	}

	else if(queueSize() == 1){
		queueFront = -1;
		queueEnd = -1;
		counter = 0;
		return;
	}

	else{
		queueFront = (queueFront + 1) % SIZE;
		counter--;
		return;
	}
}


char MyQueue::peek(){
	if(isEmpty()){
		cout << "Queue empty, cannot peek!" << endl;
		return '\0';
	}

	else return queue[queueFront];
}

int MyQueue::queueSize(){
    return counter;
}
