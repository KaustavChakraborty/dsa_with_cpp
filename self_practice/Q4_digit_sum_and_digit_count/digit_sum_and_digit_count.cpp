#include <iostream>

int main(){

    int n;
    std::cout << "Enter a number " << std::endl;
    std::cin >> n;

    if (n < 0){
        n = -n ;
    }

    //Edge case 
    if (n == 0){
        std::cout << "Digit sum:    " << 0 << std::endl; 
        std::cout << "Digit count:    " << 1 << std::endl;
    }

    else{
        int temp = n;
        int dig_sum = 0, dig_count = 0;
        while (temp > 0){
            int dig = temp%10;
            dig_sum = dig_sum + dig;
            dig_count ++;
            temp /= 10;
        }
        std::cout << "Digit sum:    " << dig_sum  << std::endl;
        std::cout << "Digit count:    " << dig_count  << std::endl;
    }

    return 0;
}