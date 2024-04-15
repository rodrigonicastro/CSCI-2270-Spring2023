#include <iostream>
#include <string>

#include "taxinfo.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 3){
        cout << "missing command line arguments" << endl;
        return -1;
    }

    TaxInfo a;
    TaxInfo* ptr;

    ptr = &a;
    
    a.inSalary = stoi(argv[1]);
    a.inTaxRate = stoi(argv[2]);


    double taxIncurred = a.inSalary * a.inTaxRate / 100;

    cout << "Salary: " << ptr->inSalary << endl;
    cout << "Tax Rate: " << ptr->inTaxRate << endl;
    cout << "Tax Incurred: " << taxIncurred << endl;
   
   return 0;
}
