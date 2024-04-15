#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 6){
        cout << "Usage: ./run_app <inputfilename> <Query_Location> <Query_Variant> <Query_Start_Age> <Query_End_Age>" << endl;
    }

    else{
        ifstream fin;
        fin.open(argv[1]);

        if(fin.fail()){
            cout << "Could not open file." << endl;
        }

        else{
            int arrCap = 10;
            int recordIdx = 0;
            int doubleCounter = 0;

            CovidCase *arr = new CovidCase[arrCap];

            string queryParams[4] = {argv[2], argv[3], argv[4], argv[5]};
            
            parseFile(fin, queryParams, arr, arrCap, recordIdx, doubleCounter);

            cout << "Array doubled: " << doubleCounter << endl;
            cout << "Total number of cases returned after the query: " << recordIdx << endl;

            CovidCase testFalse;

            testFalse.name = "Rodrigo";
            testFalse.age = 18;
            testFalse.variant = "Alpha";
            testFalse.location = "Boulder";

            CovidCase testTrue;

            testTrue.name = "Dashan Johnston";
            testTrue.age = 25;
            testTrue.variant = "Omega";
            testTrue.location = "LA";
            
            sortCases(arr, recordIdx);
            printQueriedCases(arr, recordIdx);
        }
    }
    return 0;
}