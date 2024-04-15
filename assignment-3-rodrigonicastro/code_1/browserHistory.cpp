/*************************************************************/
/*                BrowserHistory Definition                  */
/*************************************************************/
/* TODO: Implement the member functions of BrowserHistory    */
/*     This class uses a linked-list of WebPage structs to   */
/*     represent the schedule of web pages                   */
/*************************************************************/

#include "browserHistory.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
BrowserHistory::BrowserHistory() {
    /*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
    head = nullptr;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool BrowserHistory::isEmpty() {
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: prints the current list of pages 
 * in the given format.
 * [ID::1]-(URL::url1) -> ... -> NULL
 * @param none
 * @return none
 */
void BrowserHistory::displayHistory() {
    WebPage* current = head;

    cout << "== CURRENT BROWSER HISTORY ==" << endl;

    if(head != 0){
        while(current != 0){
            cout  <<  "[ID:: "  <<  current->id  <<  "]-(URL::"  <<  current->url  <<  ") -> ";
            current = current->next;
        }
    }

    else cout << "Empty History" << endl;

    cout  <<  "NULL\n===\n";
}

/*
 * Purpose: Add a new webpage to the browser history LL
 *   between the previous and the page that follows it in the list.
 * @param previousPage, the show that comes before the new page
 * @param newPage, the webpage to be added. 
 * @return none
 */
void BrowserHistory::addWebPage(WebPage* previousPage, WebPage* newPage) {
    if(previousPage == 0){
        if(head == 0) head = newPage;
        
        else{
            newPage->next = head;
            head = newPage;    
        }
        
        cout  <<  "adding: "  <<  "["  <<  newPage->id  <<  "]-"  <<  newPage->url  <<  " (HEAD)\n";
    }

    else{
        newPage->next = previousPage->next;
        previousPage->next = newPage;
        cout  <<  "adding: "  <<  "["  <<  newPage->id  <<  "]-"  <<  newPage->url  <<  " (prev: "  <<  "["  <<  previousPage->id  <<  "])\n";
    }
}

/*
 * Purpose: populates the BrowserHistory with the predetermined pages
 * @param none
 * @return none
 */
void BrowserHistory::buildBrowserHistory() {
    WebPage* colorado = new WebPage;
    colorado->url = "https://www.colorado.edu/";
    colorado->id = 10;
    colorado->views = 0;
    colorado->owner = "";
    colorado->next = NULL;

    addWebPage(NULL, colorado);

    WebPage* wikipedia = new WebPage;
    wikipedia->url = "https://www.wikipedia.org/";
    wikipedia->id = 11;
    wikipedia->views = 0;
    wikipedia->owner = "";
    wikipedia->next = NULL;

    addWebPage(colorado, wikipedia);

    WebPage* brilliant = new WebPage;
    brilliant->url = "https://brilliant.org/";
    brilliant->id = 12;
    brilliant->views = 0;
    brilliant->owner = "";
    brilliant->next = NULL;

    addWebPage(wikipedia, brilliant);

    WebPage* khan = new WebPage;
    khan->url = "https://www.khanacademy.org/";
    khan->id = 13;
    khan->views = 0;
    khan->owner = "";
    khan->next = NULL;

    addWebPage(brilliant, khan);

    WebPage* numberphile = new WebPage;
    numberphile->url = "https://www.numberphile.com/";
    numberphile->id = 14;
    numberphile->views = 0;
    numberphile->owner = "";
    numberphile->next = NULL;

    addWebPage(khan, numberphile);
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by ID and return a pointer to that node.
 * @param int id - ID of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByID(int id) {
    bool foundID = false;
    WebPage* current = head;

    if(head != 0){
        while(current != 0){
            if(current->id == id){
                foundID = true;
                break;
            }

            else current = current->next;
        }
    }
    
    
    if(foundID == false) return nullptr;

    else return current;
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by the URL and return a pointer to that node.
 * @param string url - url of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByURL(std::string url) {
    bool foundURL = false;
    WebPage* current = head;

    while(current != 0){
        if(current->url == url){
            foundURL = true;
            break;
        }

        else current = current->next;
    }
    
    if(foundURL == false) return nullptr;

    else return current;
}

/*
 * Purpose: Give an owner to a web page.
 * @param receiver - name of the show that is receiving the rating
 * @param rating - the rating that is being given to a show
 * @return none
 */
void BrowserHistory::addOwner(std::string url, string owner) {
    if(searchPageByURL(url) != 0){
        searchPageByURL(url)->owner = owner;
        cout  <<  "The owner ("  <<  owner  <<  ") has been added for the ID - "<< searchPageByURL(url)->id  <<  "\n";
    }

    else{
        cout  <<  "Page not found\n";
    }  
}

void BrowserHistory::updateViews(string url) {
    WebPage* current = head;
    int pageViews = 0;

    while(current != 0){
        if(current->url == url) pageViews = current->views + 1;

        current = current->next;
    }

    current = head;
   
    while(current != 0){
        if(current->url == url) current->views = pageViews;

        // cout << "current.views " << current->url << " " << current->views << endl;

        current = current->next;
    }
}
