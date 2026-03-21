#include <iostream>
#include <bitset>

/**
 * Swaps bits at positions i and j in a given integer n.
 * @param n The original integer
 * @param i Position of the first bit (0-indexed)
 * @param j Position of the second bit (0-indexed)
 * @return The integer with swapped bits
 */
int swapBits(int n, int i, int j) {
    // Step 1: Extract the bits at positions i and j
    int bit_i = (n >> i) & 1;
    int bit_j = (n >> j) & 1;

    // Step 2: Only swap if the bits are different
    if (bit_i != bit_j) {
        // Create a mask with 1s at positions i and j
        unsigned int mask = (1U << i) | (1U << j);
        
        // Use XOR to flip bits at those positions
        n ^= mask;
    }
    
    return n;
}

int main() {
    int n = 10; // Binary: 1010
    int i = 1, j = 2;

    std::cout << "Original: " << std::bitset<4>(n) << " (" << n << ")" << std::endl;
    
    int result = swapBits(n, i, j);
    
    std::cout << "Swapped:  " << std::bitset<4>(result) << " (" << result << ")" << std::endl;

    return 0;
}
