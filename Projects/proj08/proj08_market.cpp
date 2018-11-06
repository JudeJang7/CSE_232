/*
Created by: Jude Jang
Created on: 3/17/2018
Section: 003

Project 08
Creates a constructor for the struct Market.
Creates two methods for the struct Market.
*/

#include <fstream>
using std::ifstream;
#include <sstream>
using std::istringstream;
#include <cstddef>
#include <string>
using std::to_string;

#include "proj08_market.h"

// Populates the data member stocks.
Market::Market(string fn){
  file_name = fn;
  ifstream file(fn);
  string line;
  while (getline(file, line)){
    istringstream iss(line);
    long date;
    iss >> date;
    vector<double> prices;
    for (int i = 0; i < 30; i++){
      double price;
      iss >> price;
      prices.push_back(price);
    }
    stocks[date] = prices;
  }
}

// Returns the price of the stock on the date.
double Market::get_price(string stock, long date) const{
  if (stocks.find(date) != stocks.end() && find(symbol_list.begin(), symbol_list.end(), stock) != symbol_list.end()){
    map<long,vector<double>>::const_iterator it = stocks.find(date);
    ptrdiff_t pos = distance(symbol_list.begin(), find(symbol_list.begin(), symbol_list.end(), stock));
    return it->second.at(pos);
  }
  else 
    return -1.0;
}

// Returns high and low values for that stock for the provided year.
pair<double, double> Market::high_low_year(long year, string symbol){
  double highest = 0.0;
  double lowest = 9999.9;
  ptrdiff_t pos = distance(symbol_list.begin(), find(symbol_list.begin(), symbol_list.end(), symbol));
  for (auto pair:stocks){
    if (to_string(pair.first).substr(0,4) == to_string(year) && 
       find(symbol_list.begin(), symbol_list.end(), symbol) != symbol_list.end()){
      if (pair.second[pos] > highest)
        highest = pair.second[pos];
      if (pair.second[pos] < lowest)
        lowest = pair.second[pos];
    }    
  }
  if (highest == 0.0 && lowest == 9999.9)
    return {-1.0, -1.0};
return {highest, lowest};
}  