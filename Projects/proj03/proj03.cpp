/* 
Section: 003
Date: 2/5/18
Project 03 
*/   

#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<cmath>
using std::sqrt;
#include<string>
using std::to_string; using std::string;

string abIndex_friend(long ab_numerator, long ab_denominator, long f_pair){
  return to_string(ab_numerator) + "/" + to_string(ab_denominator) +
    ":" + to_string(f_pair);
}

// YOUR FUNCTIONS HERE

/* 
Finds the divisor sum of a number. 
*/
long divisor_sum(long n){

  long sum = 0;

  for (int i = 2; i <= sqrt(n); i++){
    if (n % i == 0){
      if (i == (n / i))
        sum += i;
      else 
        sum += (i + n / i);  
    }    
  }
  return sum + 1 + n;
}

/*
Finds the greatest common denominator between two numbers.
*/
long gcd(long a, long b){

  long d;

  while (b != 0){
    d = b;
    b = a % b;
    a = d;
  }  
  return a;
}

/*
Checks to see if a number is solitary.
*/
bool is_solitary(long n){

  if (gcd(divisor_sum(n), n) == 1)
    return true;
  else
    return false;
}

/*
Checks to see if the first number shares a 
similar abundancy index with a another number.
*/
string friendly_check(long n, long limit){

  long n_n = (divisor_sum(n) / gcd(divisor_sum(n), n)); 
  long n_d = (n / gcd(divisor_sum(n), n));

  for (long i = n + 1; i <= limit ; i++){

    long l_n = (divisor_sum(i) / gcd(divisor_sum(i), i));
    long l_d = (i / gcd(divisor_sum(i), i));

    if (n_n == l_n){
      if (n_d == l_d)
        return abIndex_friend(n_n, n_d, i);
    }    
  }    
  return abIndex_friend(n_n, n_d, -1); 
}


// MAIN

int main (){
  cout << boolalpha;   // print true or false for bools
  int test;
  cin >> test;
  switch (test) {
  case 1 : {   // divisor sum test
    long input;
    cin >> input;
    cout << divisor_sum(input) << endl;
    break;
  } // of case 1

  case 2:{    // gcd test
    long first, second;
    cin >> first >> second;
    cout << gcd(first, second) << endl;
    break;
  } // of case 2

  case 3: {    // is_solitary test
    long input;
    cin >> input;
    cout << is_solitary(input) << endl;
    break;
  } // of case 3

  case 4: {
    // friend check. Make sure the return value is the
    // result of calling abIndex_friend, a string!
    long input, limit;
    cin >> input >> limit;
    cout << friendly_check(input, limit) << endl;
    break;
  } // of case 4
    
  } // of switch
} // of main