/*
Created by: Jude Jang
Created on: 2/24/2018
Section: 003

Project 06
Creates Fibonacci n-step sequences given a limit and nstep.
Uses Fibonacci coding to encode an integer as a binary number based on the Fibonnaci n-step sequence.
*/

#include "proj06_functions.h"
#include<iostream>
using std::cin; using std::cout; using std::endl;
#include<sstream>
using std::ostringstream;
#include<iterator>
using std::ostream_iterator;
#include<algorithm>
using std::copy;

// Returns a string that represents the values in the vector.
string vec_2_str(const vector<long>& v){
  ostringstream oss;
  copy(v.begin(), v.end()-1, ostream_iterator<long>(oss, ","));
  oss << v.back();
  string s = oss.str();
  return s;
} 

// Generates a vector containing the nstep sequence.
vector<long> gen_nstep_vector(long limit, long nstep){
  long term = 1, next_term = 0;
  vector<long> v = {1, 1};

  for (int i = 2; i < nstep; i++){
    term = 2 * term;
    v.push_back(term);
  }

  int i = 0;
  while (next_term <= limit){
    for (int j = i; j < nstep + i; j++)
      next_term += v[j];
      i++;
    if (next_term <= limit){
      v.push_back(next_term);
      next_term = 0;
    }  
  }
  return v;
}

// Returns a binary string which represents num as the nstep sequence.
string num_to_nstep_coding(long num, long nstep){
  vector<long> v = gen_nstep_vector(num, nstep);
  string encode;

  for (int i = 0; i < v.size(); i++)
    encode += '0';
  
  for (unsigned i = v.size(); i > 0; i--){
    if (num - v[i] >= 0){
      num = num - v[i];
      encode[i] = '1';
    }  
  }
  encode.erase(encode.begin());
  return encode;
}

// Converts the nstep coded binary string to a long.
long nstep_coding_to_num(const string& coding, const vector<long>& nstep_sequence){
  long decoded = 0;
  for (int i = 0; i < nstep_sequence.size() - 1; i++){
    if (coding[i] == '1')
      decoded += nstep_sequence[i + 1];
  }
  return decoded;
}