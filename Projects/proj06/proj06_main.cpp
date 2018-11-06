#include "proj06_functions.h"
#include<iostream>
using std::cin; using std::cout;

int main (){

  long test_num;
  cin >> test_num;

  switch(test_num){

  case 1: {
    long input;
    vector<long> v;
    while (cin >> input)
      v.push_back(input);
    cout << vec_2_str(v);
    break;
  }

  case 2:{
    long limit, nstep;
    cin >> limit >> nstep;
    cout << vec_2_str(gen_nstep_vector(limit, nstep));
    break;
  }

  case 3:{
    long num, nstep;
    cin >> num >> nstep;
    cout << num_to_nstep_coding(num, nstep);
    break;
  }

  case 4:{
    string coding;
    long limit, nstep;
    vector<long> nstep_sequence;
    cin >> coding >> limit >> nstep;
    nstep_sequence.push_back(limit);
    nstep_sequence.push_back(nstep);
    cout << nstep_coding_to_num(coding, nstep_sequence);
    break;
  }
    
  } // of switch
}  // of main