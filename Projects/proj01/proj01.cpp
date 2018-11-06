#include<iostream>
using std::cout; using std::cin; using std::endl; using std::fixed;
#include<iomanip>
using std::setprecision;
#include<cmath>
using std::pow;

int main() {
    cout << fixed << setprecision(2);
    
    double car_price, sales_tax_rate, down_payment,
    title_and_fees, yearly_interest_rate, loan_duration;

    cin >> car_price >> sales_tax_rate >> down_payment
    >> title_and_fees >> yearly_interest_rate >> loan_duration;

    double sales_tax = car_price * sales_tax_rate;
    double cost = car_price + sales_tax + title_and_fees - down_payment;
    double monthly_rate = yearly_interest_rate / 12.0;

    double monthly_payment = cost * (monthly_rate * pow ((1 + monthly_rate), loan_duration) 
    / (pow ((1 + monthly_rate), loan_duration) - 1 ));

    cout << monthly_payment;
    
    return 0;
}

