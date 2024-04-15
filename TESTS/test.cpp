#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(){
    string _identiKey = "110638005";
    string title = "guardians of the galaxy";
    int hashKey = 1000;    
    int ASCIIsum = 0;
    int counter = 0;
    int hashIndex;

    for(int i = 0; i < title.length(); i++){
        int ASCIIchar = int(title[i]);
        
        if(ASCIIchar >= 97 && ASCIIchar <= 122) ASCIIchar -= 32;

        if(_identiKey[counter] == '0') ASCIIsum += ASCIIchar;

        else ASCIIsum += ASCIIchar*int(_identiKey[counter]);

        counter++;
        if(counter > 8) counter = 0;
    }
    
    hashIndex = ASCIIsum % hashKey;
    cout << ASCIIsum << endl;
    cout << hashIndex << endl;
}