#include "array_double.hpp"
#include <sstream>

void parseFile(ifstream& input,string queryParams[], CovidCase *&cases, int &arrCapacity,  int &recordIdx, int &doublingCounter){
    while(!input.eof()){
        int x = 0;
        string line; 
        string lineInfo[4];
        getline(input, line);
        stringstream currentCase(line);

        while(getline(currentCase, line, ',')){
            lineInfo[x] = line;
            x++;
        }

        if(lineInfo[1] == queryParams[1] && lineInfo[2] == queryParams[0] && (stoi(lineInfo[3]) >= stoi(queryParams[2]) && stoi(lineInfo[3]) <= stoi(queryParams[3]))){
            CovidCase caseToAdd;

            caseToAdd.name = lineInfo[0];
            caseToAdd.variant = lineInfo[1];
            caseToAdd.location = lineInfo[2];
            caseToAdd.age = stoi(lineInfo[3]);

            addCase(cases, caseToAdd, arrCapacity, recordIdx, doublingCounter);
        }
    }
}

bool isCaseQueried(CovidCase covidCase, string queryLocation, string queryVariant, int startAge, int endAge) {
    if(covidCase.location == queryLocation && covidCase.variant == queryVariant && (covidCase.age >= startAge && covidCase.age <= endAge)){
        return true;
    }
    
    else{
        return false;
    }
}

void resizeArr(CovidCase *&cases, int *arraySize){
    int newCapacity = *arraySize * 2;
    CovidCase *newArray = new CovidCase[newCapacity]; 

    for(int i = 0; i < *arraySize; i++){
        newArray[i] = cases[i];
    }

    cases = newArray;

    *arraySize = newCapacity;
}

void addCase(CovidCase *&cases, CovidCase covidCase, int &arrCapacity, int &recordIdx, int &doublingCounter){
    if(recordIdx == arrCapacity){
        resizeArr(cases, &arrCapacity);
        doublingCounter++;
    }
    
    cases[recordIdx] = covidCase;
    recordIdx++;
}

void sortCases(CovidCase* cases, int length) {
    for(int i = 0; i < length; i++){		        
		for(int j = i+1; j < length; j++){
			if(cases[i].age > cases[j].age){
				CovidCase temp = cases[i];
				cases[i] = cases[j];
				cases[j] = temp;
			}

            else if(cases[i].age == cases[j].age){
                if(cases[i].name > cases[j].name){
				    CovidCase temp = cases[i];
				    cases[i] = cases[j];
				    cases[j] = temp;
			    }
            }
		}
	}
}

void printQueriedCases(CovidCase* cases, int numOfRecords) {    
    cout << "Queried Cases" << endl;
    cout << "---------------------------------------" << endl;

    for(int i = 0; i < numOfRecords; i++){
        cout << cases[i].name << " " << cases[i].age << endl;
    }
}