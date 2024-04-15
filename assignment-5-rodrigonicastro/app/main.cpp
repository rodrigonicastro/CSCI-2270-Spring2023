#include<iostream>
#include <fstream>
#include<cmath>
#include<iomanip>
#include "../code/MessageDecoder.hpp"

using namespace std;


int main(int argc, char* argv[])
{
   if (argc < 2) {
        cout << "Usage: ./run_app <inputfilename>" << endl;
        return 0;
    } 
    
    else {
        string filename = argv[1];
        
        ifstream fin;
        fin.open(filename);

        if(fin.fail()) cout << "Error: Could not open file.\n";

        else{
          string jumbled_str;

          while(!fin.eof()){
            string line;
            getline(fin, line);

            jumbled_str = line;
          }

          MessageDecoder messageDecoder;

          messageDecoder.generate_operator_queue(jumbled_str);

          string postfix = messageDecoder.generate_postfix(jumbled_str);
          int finalAnswer = messageDecoder.evaluate_postfix(postfix);

          cout << "Postfix Notation::" << postfix << endl;
          cout << "Final Answer::" << finalAnswer << endl;
        }

        return 0;
    }
    
  return 0;
}