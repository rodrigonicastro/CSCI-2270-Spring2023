#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "../code_1/browserHistory.hpp"

using namespace std;

void displayMenu();

int main(int argc, char* argv[]) {
    if(argc>1) {
        freopen(argv[1],"r",stdin);
    }

    BrowserHistory browserHistory = BrowserHistory();

    int menuOption = 1;

    while(menuOption != 6){
        displayMenu();
        cin >> menuOption;

        switch(menuOption){
            case 1:{
                browserHistory.buildBrowserHistory();
                browserHistory.displayHistory();
                break;
            }

            case 2:{
                browserHistory.displayHistory();
                break;
            }

            case 3:{
                WebPage* newPage = new WebPage;
                WebPage* previous;

                cout << "Enter the new web page's url:" << endl;
                cin >> newPage->url;

                cout << "Enter the new web page's id:" << endl;
                cin >> newPage->id;

                while(browserHistory.searchPageByID(newPage->id) != 0){
                    cout << "This ID already exists. Try again." << endl;
                    cout << "Enter the new web page's id:" << endl;
                    cin >> newPage->id;
                }
                
                cout << "Enter the previous page's url (or First):" << endl;
                string prevURL;
                cin >> prevURL;

                if(prevURL == "First"){
                    browserHistory.addWebPage(NULL, newPage);
                    browserHistory.updateViews(newPage->url);
                }

                else{
                    previous = browserHistory.searchPageByURL(prevURL);

                    while(previous == 0 && prevURL != "First"){
                        cout << "INVALID(previous page url)... Please enter a VALID previous page url!" << endl;
                        cout << "Enter the previous page's url (or First):" << endl;
                        cin >> prevURL;

                        previous = browserHistory.searchPageByURL(prevURL);
                    }

                    browserHistory.addWebPage(previous, newPage);
                    browserHistory.updateViews(newPage->url);
                }


                // browserHistory.displayHistory();

                break;
            }

            case 4:{
                cout << "Enter url of the web page to add the owner:" << endl;
                string URL;
                cin >> URL;

                cout << "Enter the owner:";
                string owner;
                cin.ignore();
                getline(cin, owner);

                browserHistory.addOwner(URL, owner);

                break;
            }
        
            case 5:{
                cout << "Enter url of the web page to check the view count: " << endl;
                string URL;
                cin >> URL;

                while(browserHistory.searchPageByURL(URL) == 0){
                    cout << "Page not found. Try again.\nEnter url of the web page to check the view count: " << endl;
                    cin >> URL;
                }

                cout << "View count for URL - " << URL << " is " << browserHistory.searchPageByURL(URL)->views << endl;

                break;
            }
            
            case 6:{
                cout << "Quitting...Goodbye!\n";
                break;
            }
        
            default:{
                cout << "Invalid option" << endl;
                break;
            }
        }
    }
    
    return 0;
}




/************************************************
           Definitions for main_1.cpp
************************************************/
void displayMenu()
{
    // COMPLETE: You DO NOT need to edit this
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build history " << endl;
    cout << " 2. Display history " << endl;
    cout << " 3. Add web page " << endl;
    cout << " 4. Add owner" << endl;
    cout << " 5. View count for a web page" << endl;
    cout << " 6. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
