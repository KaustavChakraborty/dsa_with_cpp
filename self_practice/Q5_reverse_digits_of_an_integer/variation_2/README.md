# Palindrome Number (Half-Reverse Optimization)

An optimized C++ implementation to determine if an integer is a palindrome without converting it to a string and without risking integer overflow.

---

## 📝 Problem Statement
Given an integer `x`, return `true` if `x` is a palindrome, and `false` otherwise.

**Constraints & Requirements:**
- **No String Conversion:** The problem must be solved using mathematical operations.
- **Overflow Safety:** The solution must not crash or produce incorrect results if the reversed version of the number exceeds the `int` range.
- **Negative Numbers:** Negative numbers (e.g., -121) are not palindromes because they read as `121-` from right to left.

---

## ⚙️ The Algorithm: "Reversing the Second Half"
To avoid the overflow that occurs when reversing very large numbers, we only reverse the **last half** of the digits and compare it with the **first half**.

### Key Steps:
1. **Sanity Check:** If the number is negative or ends in a zero (and isn't zero itself), it cannot be a palindrome.
2. **The Midpoint:** We peel digits from the original number and add them to a `revertedNumber`. We know we've reached the middle when the `revertedNumber` becomes greater than or equal to the remaining `x`.
3. **Comparison:** - If the number has an **even** number of digits, `x` will equal `revertedNumber`.
   - If the number has an **odd** number of digits, we discard the middle digit (the last digit of `revertedNumber`) by dividing by 10 before comparing.



---

## 📊 Performance
- **Time Complexity:** $O(\log_{10} N)$ — We only process half of the digits in the number.
- **Space Complexity:** $O(1)$ — We use a constant amount of extra space.

---

## 💻 Implementation

```cpp
#include <iostream>

/**
 * Checks if an integer is a palindrome by reversing only its second half.
 * This prevents potential integer overflow for large inputs.
 */
bool isPalindrome(int x) {
    // 1. Handle edge cases
    // Negative numbers and numbers ending in 0 (except 0 itself) are not palindromes
    if (x < 0 || (x % 10 == 0 && x != 0)) {
        return false;
    }

    int revertedNumber = 0;
    
    // 2. Reverse the second half of the number
    while (x > revertedNumber) {
        revertedNumber = (revertedNumber * 10) + (x % 10);
        x /= 10;
    }

    // 3. Check for equality
    // Even digits: x == revertedNumber (e.g., 12 == 12)
    // Odd digits: x == revertedNumber / 10 (e.g., 12 == 123/10)
    return x == revertedNumber || x == revertedNumber / 10;
}

int main() {
    int n;
    std::cout << "Enter an integer: ";
    if (!(std::cin >> n)) return 1;

    if (isPalindrome(n)) {
        std::cout << n << " is a palindrome." << std::endl;
    } else {
        std::cout << n << " is not a palindrome." << std::endl;
    }

    return 0;
}
