#include <iostream>

int main() {
    int a = 10;
    float b = 3.14f;

    std::cout << "Before Swap: a = " << a << ", b = " << b << std::endl;

    // Step 1: Store the integer value in a temporary float to prevent early loss
    float temp = static_cast<float>(a);

    // Step 2: Assign b to a (requires casting/truncation)
    a = static_cast<int>(b);

    // Step 3: Assign temp to b
    b = temp;

    std::cout << "After Swap:  a = " << a << ", b = " << b << std::endl;

    return 0;
}
