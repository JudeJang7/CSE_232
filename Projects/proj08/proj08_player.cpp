/*
Created by: Jude Jang
Created on: 3/17/2018
Section: 003

Project 08
Creates four methods for the struct Market.
*/

#include <sstream>
using std::ostringstream; 
#include<iomanip>
using std::fixed; using std::setprecision;

#include "proj08_player.h"

// Attempts to buy a stock by the player from the Market on the specified date.
bool Player::buy(Market &m, string stock, long date, long quantity){
  if (cash > quantity * m.get_price(stock, date) && 
     find(m.symbol_list.begin(), m.symbol_list.end(), stock) != m.symbol_list.end() && 
     m.stocks.find(date) != m.stocks.end()){
    cash = cash - (quantity * m.get_price(stock, date)); 
    stocks[stock] += quantity; 
    return true;
  }
  else
    return false;
}

// Attempts to sell a stock by the player from the Market on the specified date.
bool Player::sell(Market &m, string stock, long date, long quantity){
  if (stocks.find(stock) != stocks.end() && stocks[stock] >= quantity && m.stocks.find(date) != m.stocks.end()){
    cash += quantity * m.get_price(stock, date);
    stocks[stock] = stocks[stock] - quantity;
    if (stocks[stock] == 0)
      stocks.erase(stock);
    return true;
  }
  else
    return false;
}

// Returns a string representation of the player.
string Player::to_str(){
  ostringstream oss;
  oss << fixed << setprecision(2);
  oss << cash;
  for(auto ele: stocks)
    oss << "," << ele.first << ":" << ele.second;
  return oss.str();
}

// Returns a new player that has, as a combination, all the cash and stocks of the two players.
Player Player::combine(Player& p2){
  Player p3;
  for (auto ele: stocks){
    if (p3.stocks.find(ele.first) != p3.stocks.end())
      p3.stocks[ele.first] += stocks[ele.first];
    else
      p3.stocks[ele.first] = stocks[ele.first];
  }
  for (auto ele: p2.stocks){
    if (p3.stocks.find(ele.first) != p3.stocks.end())
      p3.stocks[ele.first] += p2.stocks[ele.first];
    else
      p3.stocks[ele.first] = p2.stocks[ele.first];
  }
  p3.cash = cash + p2.cash;
  cash = 0.0;
  p2.cash = 0.0;
  stocks.erase(stocks.begin(),stocks.end());
  p2.stocks.erase(p2.stocks.begin(), p2.stocks.end());
  return p3;
}