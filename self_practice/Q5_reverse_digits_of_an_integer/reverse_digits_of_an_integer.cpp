#include <iostream>

int main(){

    long long n;
    std::cout << "Enter the integer" << std::endl;
    std::cin >> n;

    bool is_negative = (n < 0);
    if (is_negative) n = - n;

    long long reversed = 0;

    while (n > 0){
        int digit = n % 10;
        reversed = reversed * 10 + digit;
        n /= 10 ;
    }

    if (is_negative) reversed = -reversed;

    std::cout << "Reverse number is:    " << reversed << std::endl;

    return 0;
}