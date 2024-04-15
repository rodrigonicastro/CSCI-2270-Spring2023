#include <iostream>
#include <fstream>
#include "../code/fundamentals.hpp"
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 3){
        cout << "File name(s) not provided." << endl;
    }

    else{
        int index = 0;        
        int num_companies = 0;

        string file_name = argv[1];
        string file_dir = file_name;
        string line, companyName, stock1Value, stock2Value, stock3Value, stock4Value, stock5Value;

        ifstream fin;
        fin.open(file_dir);

        if(fin.fail()){
            cout << "Could not open file." << endl;
        }

        else{
            while(!fin.eof()){
                getline(fin, line);
                num_companies++;                
            }

            fin.close();            

            stockInfo stocks[num_companies];

            fin.open(file_dir);

            string lastChar;

            for(int i = 0; i < file_name.length(); i++){
                if(file_name[i] == '.'){
                    lastChar = file_name[i-1];
                }
            }

            string outFile = argv[2];

            ofstream fout;
            fout.open(outFile);

            while(!fin.eof()){
                double stock_prices[5];
                string lineInfo[6];
                int x = 0;

                getline(fin, line);
                stringstream currentStock(line);

                while(getline(currentStock, line, ',')){
                    lineInfo[x] = line;
                    x++;
                }
                
                companyName = lineInfo[0];

                for(int i = 1; i < 6; i++){
                    stock_prices[i-1] = stod(lineInfo[i]);
                }

                insertStockInfo(stocks, companyName, stock_prices, index);                

                displaySortedStocks(stocks[index], fout);

                

                index++;
            }
            fout.close();
        }        
    }
    return 0;
}