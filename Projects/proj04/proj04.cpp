/*
Section 003
2/12/2018
Project 4
*/

#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string; using std::to_string;
#include<cmath>

const string the_chars = "0123456789abcdef";

// Functions

// Reverses a string.
string reverse_string(string input){
  string reverse;
  for (int i = input.size() - 1; i >= 0; i--){
    reverse += input[i];
  }
  return reverse;
}

// Checks to see if string is a palindrome.
bool is_palindrome(string input){
  string reverse = reverse_string(input);
  if (reverse == input)
    return true;
  else
    return false;  
}

// Changes a long to a long in a different base system.
string long_to_base(long n, long base){
  string result;
  while (n > 0){
    long quotient = n / base;
    long remainder = n % base;
    if (base == 16)
      result += the_chars[remainder];
    if (base == 2)
      result += to_string(remainder); 
    n = quotient;
  }
  return reverse_string(result);
}

// Checks to see if a long is prime.
bool is_prime(long n){
  for (int i = 2; i <= n / 2; ++i){
    if (n % i == 0)
      return false;
  }    
  return true; 
}

// Checks to see if a long is a palindromic prime number.
string is_pal_prime(long n){
  string binary = long_to_base(n, 2);
  string hex = long_to_base(n, 16);
  if (is_prime(n)){
    if (is_palindrome(to_string(n)) == true)
   return "decimal-pal-prime";
  if (is_palindrome(binary) == true)
    return "binary-pal-prime";
  if (is_palindrome(hex) == true)  
    return "hex-pal-prime";
  }
  return "not-pal-prime";  
}

// Main

int main (){
  long test_num;
  cin >> test_num;
  cout << boolalpha;

  switch(test_num) {

  case 1: {
    string input;
    cin >> input;
    cout << reverse_string(input);
    break;
  }

  case 2:{
    string input;
    cin >> input;
    cout << is_palindrome(input);
    break;
  }

  case 3:{
    long n, base;
    cin >> n >> base;
    cout << long_to_base(n,base);
    break;
  }

  case 4:{
    long n;
    cin >> n;
    cout << is_prime(n);
    break;
  }

  case 5:{
    long n;
    cin >> n;
    cout << is_pal_prime(n);
    break;
  }
    
  } // of switch
}  // of main