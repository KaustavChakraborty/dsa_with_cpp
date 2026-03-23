#include <iostream>

int main(){

    int n;
    std::cout << "Enter an integer:     " << std::endl;
    std::cin >> n ;

    // Method 1: Modulo
    if (n%2 == 0) 
        std::cout << "method 1: Even\n";
    else 
        std::cout << "method 1: Odd\n";

    // Method 2: bitwise AND
    // The last bit of any integer is 1 for odd, 0 for even.
    // n & 1 isolates the LSB (least significant bit).
    // This is faster than modulo since it avoids division entirely.
    if (n & 1)
        std::cout << "method 2: Odd\n";
    else 
        std::cout << "method 2: Even\n";


    return 0;
}