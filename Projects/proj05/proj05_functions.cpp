/*
Section: 03
Date: 2/11/18
Project 05: Ciphers
*/

#include "proj05_functions.h"
#include<iostream>
using std::cin; using std::cout; using std::endl;
#include<string>
using std::string; 

// Returns a new string that is all lowercase and consists of only alphabetic characters in s
string clean_string(string s){
  string clean_str;
  for (char c : s){
    if (isalpha(c))
      clean_str += (char)tolower(c);
  } 
  return clean_str;
}

// Takes in a key, and returns a keyword encoding
string create_encoding(string key){
  string alphabet = "abcdefghijklmnoprstuvwxyz";
  string key_encode;

  for (long i = 0; i < key.length(); i++){
    if (key_encode.find(key[i]) == std::string::npos && key[i] != 'q')
      key_encode += key[i];
  }

  for (long i = 0; i < alphabet.length(); i++){
    if (key_encode.find(alphabet[i]) == std::string::npos)
      key_encode += alphabet[i];
  }
  return key_encode;
}

// Converts the digraph string dg to its encoded digraph
string encode_digraph(string dg, string block1, string block2){
  string alphabet = "abcdefghijklmnoprstuvwxyz";

  long index0 = alphabet.find(dg[0]);
  long index1 = alphabet.find(dg[1]);

  long col1 = index0 % 5;
  long col2 = index1 % 5;
  long row1 = index0 / 5;
  long row2 = index1 / 5;
  
  long block1_index = row1 * 5 + col2;
  long block2_index = row2 * 5 + col1;

  string block1_ci = create_encoding(block1);
  string block2_ci = create_encoding(block2);

  string encode_di;
  encode_di += block1_ci[block1_index];
  encode_di += block2_ci[block2_index];
  
  return encode_di;
}

// Converts the encoded digraph string dg to its original digraph 
string decode_digraph(string dg, string block1, string block2){
  string block1_ci = create_encoding(block1);
  string block2_ci = create_encoding(block2);

  long index0 = block1_ci.find(dg[0]);
  long index1 = block2_ci.find(dg[1]);
  
  long col1 = index0 % 5;
  long col2 = index1 % 5;
  long row1 = index0 / 5;
  long row2 = index1 / 5;
  
  long block1_index = row1 * 5 + col2;
  long block2_index = row2 * 5 + col1;
  
  string alphabet = "abcdefghijklmnoprstuvwxyz";
  string decode_di;
  decode_di += alphabet[block1_index];
  decode_di += alphabet[block2_index];
  
  return decode_di;
}

// Returns a string which is the encoding of the message
string encode(string msg, string key1, string key2){
  if (msg.length() % 2 == 1)
    msg += "x";

  string clean_str = clean_string(msg); 
  string dg, encode_str;

  for (int i = 0; i < clean_str.length() - 1; i += 2){
    dg = clean_str.substr(i, 2);
    encode_str += encode_digraph(dg, key1, key2);
  }
  return encode_str;
}

// Returns a string which is the decoding of the message
string decode(string msg, string key1, string key2){
  string clean_str = clean_string(msg); 
  string dg, decode_str;

  for (int i = 0; i < clean_str.length() - 1; i += 2){
    dg = clean_str.substr(i, 2);
    decode_str += decode_digraph(dg, key1, key2);
  }
  return decode_str;
}