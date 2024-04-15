
#include "BrowserHistory.hpp"

BrowserHistory::BrowserHistory()
{
    // No changes needed
}

BrowserHistory::~BrowserHistory()
{
    // No changes needed
}

/*
 * Purpose: Has to detect if a defect is present in the linkedlist pointed by head
 * @param none
 * @return integer length of defect if one exists. If defect not present return -1
 */
int BrowserHistory::findDefectLength(){
    WebPage* fast = head;
    WebPage* slow = head;

    bool isDefect = false;

    while(fast != 0){
        if(fast->next != 0){
            fast = fast->next->next;
            slow = slow->next;

            if(fast == slow){
                isDefect = true;
                break;
            }
        }
        else break;
    }

    if(isDefect == true){        
        fast = fast->next;          
        int defectLength = 1;

        while(fast != NULL){
            if(fast == slow) break;

            else{
                fast = fast->next;
                defectLength++;
            }   
        }

        return defectLength;         
    }

    else return -1;
}

/*
 * Purpose: Has to remove all the WebPage nodes from [start, end] inclusive.
 * Has to print appropriate messages on cout like below if the linkedlist is empty
 * or if the values of start/ end are improper
 * follow the same order for couts in the writeup - check empty list first, then check wrong start/end values
 * @param integers start and end (1 based indexing not 0 based)
 * @return none
 */
void BrowserHistory::removeWebPages(int start, int end){
    int listLength = 0;

    WebPage* temp = head;

    while(temp != 0){
        temp = temp->next;
        listLength++;
    }
    
    if(head == 0){
        cout << "Browsing history is Empty" << endl;
        return;
    }

    else if(start < 1 || end > listLength || start > end){
        cout << "Invalid start or end values" << endl;
    }

    else{
        int counter = 1;

        if(start == 1){
            WebPage* curr = head;
            head = head->next;

            while(counter <= end){
                curr = curr->next;

                counter ++;
            }

            head = curr;
        }
        
        else{
            WebPage* curr = head;
            WebPage* next = head->next;

            while(counter < start && curr != 0){                
                next = next->next;

                counter++;
                if(counter == start) break;

                curr = curr->next;
            }

            while(counter < end && next != 0){
                next = next->next;
                
                counter++;
            }

            curr->next = next;
        }    
    }
}


/*
 * Purpose: Interweave the webpages alternatively into a new linkedlist 
 * starting with the first webpage in the list one
 * Assign the head of the new interweaved list to the head of this BrowserHistory
 * DO NOT create new nodes and copy the data, just use the same nodes from one and two and change pointers
 * If one of them runs out of length append the remaining of the other one at end
 * @param two linkedlist heads one and two
 * @return none
 */
void BrowserHistory::mergeTwoHistories(WebPage *headOne, WebPage * headTwo){
    if(headOne == NULL && headTwo == NULL){
        head = nullptr;
        // cout << "Browsing history is Empty" << endl;
    }

    else if(headOne == NULL){
        head = headTwo;
    }

    else if(headTwo == NULL){
        head = headOne;
    }

    else{
        head = headOne;
        WebPage* tempOne = headOne->next;
        WebPage* tempTwo = headTwo;
        WebPage* curr = head;
        bool isPrevOne = true;

        while(tempOne != 0 || tempTwo != 0){
            if(tempOne != 0 && tempTwo != 0){
                if(isPrevOne){
                    curr->next = tempTwo;
                    curr = curr->next;
                    tempTwo = tempTwo->next;

                    isPrevOne = false;
                }

                else{
                    curr->next = tempOne;
                    curr = curr->next;
                    tempOne = tempOne->next;

                    isPrevOne = true;
                }
            }
            
            else if(tempOne == 0 && tempTwo != 0){
                curr->next = tempTwo;
                curr = curr->next;
                tempTwo = tempTwo->next;
            }

            else if(tempOne != 0 && tempTwo == 0){
                curr->next = tempOne;
                curr = curr->next;
                tempOne = tempOne->next;
            }
        }
    }
}
