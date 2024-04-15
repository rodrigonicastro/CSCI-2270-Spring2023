#include <iostream>
#include <cstdlib>
#include "MessageDecoder.hpp"

using namespace std;
# define SIZE 50

MessageDecoder::MessageDecoder()
{
	my_queue = new MyQueue();
	my_stack = new MyStack();
}

MessageDecoder::~MessageDecoder()
{
    delete my_queue;
    delete my_stack;	
}

/*
    generate_operator_queue(string jumbled_str)

    Takes the jumbled string as the input parameter and stores all the allowed operators in my_queue
*/
void MessageDecoder::generate_operator_queue(std::string jumbled_str){
    int strLength = jumbled_str.length();

    for(int i = 0; i < strLength; i++){
        char curr = jumbled_str[i];
        if(curr == '+' || curr == '-' || curr == '*'){
            my_queue->enqueue(curr);
        }
    }

    // for(int i = 0; i < my_queue->queueSize(); i++){
    //     cout << my_queue->getQueue()[i] << endl;
    // }
    
}

/*
    generate_postfix(string jumbled_str)

    Takes the jumbled string as the input parameter and computes a postfix expression using the populated my_queue
    returns a postfix expression
*/
string MessageDecoder::generate_postfix(std::string jumbled_str){
    int counter = 0;
    int queueCounter = 0;
	string postfix = "";

    int strLength = jumbled_str.length();

    for(int i = 0; i < strLength; i++){
        char curr = jumbled_str[i];
        int asciiChar = int(curr);

        if(asciiChar >= 48 && asciiChar <= 57){
            postfix += curr;
            counter++;
        }

        if(counter == 2){
            counter = 0;
            postfix += my_queue->getQueue()[queueCounter];
            queueCounter++;
        }
    }

    while(queueCounter < my_queue->queueSize()){
        postfix += my_queue->getQueue()[queueCounter];
        queueCounter++;
    }

    return postfix;
}

/* 
    evaluate_postfix(string postfix) 

    Takes the post fix string as an input parameter and evaluates the post fix string. 
    returns an integer after evaluating the postfix expression
*/

int MessageDecoder::evaluate_postfix(std::string postfix){

    int postfixLength = postfix.length();

    for(int i = 0; i < postfixLength; i++){
        char curr = postfix[i];
        int asciiChar = int(curr);


        if(asciiChar >= 48 && asciiChar <= 57){
            int valToPush = atoi(&curr);
            my_stack->push(valToPush);
        }

        else{
            int num1 = my_stack->peek()->val;  
            my_stack->pop();

            int num2 = my_stack->peek()->val;
            my_stack->pop();

            int answer;

            if(curr == '+') answer = num2 + num1;

            else if(curr == '-') answer = num2 - num1;

            else answer = num2 * num1;

            my_stack->push(answer);
        }
    }
    return my_stack->peek()->val;
}

//For Testing purposes only!
MyQueue* MessageDecoder::getQueue(){
    return my_queue;
}

//For Testing purposes only!
MyStack* MessageDecoder::getStack(){
    return my_stack;
}