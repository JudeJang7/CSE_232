#include<iostream>
using std::cin; using std::cout; using std::endl;
#include<cmath>
using std::pow; using std::sqrt; using std::floor;

int main(){
  long beginning, ending, print, sequence, val, compare = 0, biggest = 0, big_seq = 0, long_seq = 0, longest = 0;
  cin >> beginning >> ending >> print;

  if ((beginning && ending > 2) && (ending > beginning) && (print == 1 || print == 0)){
    for (sequence = beginning; sequence <= ending; sequence++){
      val = sequence;
      compare = 0;
      if (print == 1){
        cout << sequence << ": ";
      }
      
      while (val != 1){
        if (val % 2 == 0){
          compare++;
          if (print == 1){
            if (floor(sqrt(val)) == 1)
              cout << floor(sqrt(val)) << endl;
            else 
              cout << floor(sqrt(val)) << ",";
          }
          val = floor(sqrt(val));
        }
        else if (val % 2 == 1){
          compare++;
          if (print == 1){
            if (floor(pow(val,1.5)) == 1)
              cout << floor(pow(val,1.5)) << endl;
            else 
              cout << floor(pow(val,1.5)) << ",";
          }
          val = floor(pow(val,1.5));
        }
        if (val > biggest){
          biggest = val;
          big_seq = sequence;
        }
      }
        if (compare > longest){
          longest = compare;
          long_seq = sequence;
      }
    }
    cout << long_seq << ", " << longest << endl;  
    cout << big_seq << ", " << biggest << endl;
  }
  else 
    cout << "Error" <<endl;
}
