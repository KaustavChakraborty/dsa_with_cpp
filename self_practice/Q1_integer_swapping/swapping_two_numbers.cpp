#include <iostream>

int main()
{
    int a = 15, b = 12;

    // Method 1: using temporary variable

    int temp = a;
    a = b;
    b = temp;
    std::cout << "method 1 (temp) : a = " << a << " , b = " << b << "\n";

    a = 15, b = 12;

    //Method 2: using arithmatic 
    // WARNING: Can overflow for large integers

    a = a + b;
    b = a - b;
    a = a - b;
    std::cout << "method 2 (arithmatic) : a = " << a << " , b = " << b << "\n";

    a = 15, b = 12;

    // Method 3: XOR bitwise swap

    a = a ^ b;   // a holds XOR of both
    b = a ^ b;   // b = (a^b)^b = a (original a recovered)
    a = a ^ b;   // a = (a^b)^a = b (original b recovered)
    std::cout << "Method 3 (XOR):  a = " << a << ", b = " << b << "\n";

    return 0;
}