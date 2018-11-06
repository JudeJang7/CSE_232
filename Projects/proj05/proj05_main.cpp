#include "proj05_functions.h"
#include<iostream>
using std::cin; using std::cout; using std::endl;
#include<string>
using std::string; 

int main (){
  long test_num;
  cin >> test_num;

  switch(test_num) {

  case 1: {
    string s;
    cin.ignore();
    getline(cin, s);
    cout << clean_string(s) << endl;
    break;
  }

  case 2:{
    string key;
    cin >> key;
    cout << create_encoding(key) << endl; 
    break;
  }

  case 3:{
    string dg, block1, block2;
    cin >> dg >> block1 >> block2;
    cout << encode_digraph(dg, block1, block2) << endl;
    break;
  }

  case 4:{
    string dg, block1, block2;
    cin >> dg >> block1 >> block2;
    cout << decode_digraph(dg, block1, block2) << endl;
    break;
  }

  case 5:{
    string msg, key1, key2;
    cin.ignore();
    getline(cin, msg);
    cin >> key1 >> key2;
    cout << encode(msg, key1, key2) << endl;
    break;
  }

  case 6:{
    string msg, key1, key2;
    cin.ignore();
    getline(cin, msg);
    cin >> key1 >> key2;
    cout << decode(msg, key1, key2) << endl;
    break;
  }

  } // of switch
}  // of main