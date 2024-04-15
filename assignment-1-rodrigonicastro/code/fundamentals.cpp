#include "fundamentals.hpp"

void insertStockInfo(stockInfo stocks[], string company_name, double stock_prices_arr[], int index) {
    stockInfo stock;

    stock.company_name = company_name;    
    double total = 0;

    for(int i = 0; i < 5; i++){ 
        stock.stock_prices_arr[i] = stock_prices_arr[i];     
        total += stock_prices_arr[i];
    }

    double average = total/5;

    stock.average = average;

    stocks[index] = stock;
}

void displaySortedStocks(stockInfo stock, ofstream& file){
    for(int i = 0; i < 5; i++){		
		for(int j = i+1; j < 5; j++){
			if(stock.stock_prices_arr[i] > stock.stock_prices_arr[j]){
				double temp = stock.stock_prices_arr[i];
				stock.stock_prices_arr[i] = stock.stock_prices_arr[j];
				stock.stock_prices_arr[j] = temp;
			}
		}
	}

//    vector<string> fileLines;

//    ifstream fin;
//    fin.open("../out_1.csv");

    // while(!fin.eof()){
    //     string line;
    //     getline(fin, line);

    //     if(line != ""){
    //         fileLines.push_back(line);
    //     }
    // }

    // fin.close();

    // file.open("../out_1.csv");

    // for(int i = 0; i < fileLines.size(); i++){
    //     file << fileLines[i] << endl;
    // }

    file << stock.company_name << "," << stock.average;

    for(int i = 0; i < 5; i++){
        file << "," << stock.stock_prices_arr[i];
    }

    file << endl;

    cout << stock.company_name << "," << stock.average;

    for(int i = 0; i < 5; i++){
        cout << "," << stock.stock_prices_arr[i];
    }

    cout << endl;
}