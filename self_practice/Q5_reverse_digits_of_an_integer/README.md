# Q5 — Reverse a Number

## Problem Statement

Given an integer N (positive, negative, or zero), reverse its decimal digits. Leading zeros in the reversed number are dropped (e.g., 100 → 1). If the reversed number overflows a 32-bit signed integer (`INT_MIN` to `INT_MAX`), return 0.

---

## Test Cases

| Test | Input | Expected | Notes |
|------|-------|----------|-------|
| TC1 | 123 | 321 | Standard |
| TC2 | -123 | -321 | Negative |
| TC3 | 100 | 1 | Trailing zeros become leading zeros (dropped) |
| TC4 | 0 | 0 | Zero |
| TC5 | 1 | 1 | Single digit |
| TC6 | -10 | -1 | Negative with trailing zero |
| TC7 | 1534236469 | 9646324351 | Overflows 32-bit → return 0 |
| TC8 | INT_MAX (2147483647) | 7463847412 | Overflows → return 0 |
| TC9 | INT_MIN (-2147483648) | Overflow → 0 | Overflow |
| TC10 | 1000000003 | 3000000001 | Just barely overflows |

---

## Algorithm Description

The algorithm constructs the reversed number digit-by-digit using the same `% 10` and `/ 10` technique as the digit-sum problem, but instead of summing the digits, it builds a new number by appending each extracted digit to the right.

```
n = 4563

reversed = 0
Step 1: digit = 3, reversed = 0*10 + 3 = 3,    n = 456
Step 2: digit = 6, reversed = 3*10 + 6 = 36,   n = 45
Step 3: digit = 5, reversed = 36*10 + 5 = 365, n = 4
Step 4: digit = 4, reversed = 365*10 + 4 = 3654, n = 0
Loop ends.
Result: 3654
```

**Overflow detection strategy:** The intermediate `reversed` variable is stored as `long long` (64-bit), allowing it to exceed 32-bit bounds. After the loop completes, compare `reversed` against `INT_MAX` and `INT_MIN`. If out of range, return 0. This is the approach used in LeetCode Problem 7 ("Reverse Integer").

**Alternative overflow detection (without long long):** Before each `reversed = reversed * 10 + digit` step, check:
- If `reversed > INT_MAX / 10` → next multiplication will overflow
- If `reversed == INT_MAX / 10 && digit > 7` → next addition will overflow (since INT_MAX ends in 7)
This approach stays entirely within 32-bit arithmetic.

---

## Time and Space Complexity

**Time:** O(d) where d is the number of digits in N. For fixed 32-bit integers, d ≤ 10, making this O(1) in practice. In general, O(log₁₀ N).

**Space:** O(1) — three variables: `reversed`, `sign`, `temp`. No data structures.

---

## Variations and Related Problems

### Variation 1 — Reverse a String (Different mechanism)
Reversing a string uses the two-pointer technique: swap characters at positions `left` and `right`, then move them inward. Time O(N), Space O(1). The core insight — reverse by swapping from both ends — generalizes to arrays, linked lists, and partial reversal in place.

### Variation 2 — Check Palindrome Using Reverse
A number is a palindrome iff `reverse(N) == N`. But computing the full reverse risks overflow for large numbers. The optimized check (LeetCode 9) reverses only half the digits, comparing them with the other half — elegant overflow avoidance.

### Variation 3 — Reverse Words in a Sentence
"Hello World" → "World Hello". Reverse the entire string, then reverse each word individually. This is O(N) time, O(1) extra space (in-place). Demonstrates that reversal is a composable operation.

### Variation 4 — Reverse a Number in Base B
Instead of dividing/multiplying by 10, divide/multiply by B. Reverses the digit sequence in any base. Useful for binary reversal (bit reversal), relevant in FFT algorithms where bit-reversal permutation is a preprocessing step.

### Variation 5 — Rotate Digits by K Positions
"12345" rotated by 2 → "34512". Extract last K digits, prepend them. Uses modular arithmetic on the number.

### Variation 6 — Next Greater Number with Same Digits
Find the next permutation of digits that forms a larger number (e.g., 1234 → 1243). This is the "next permutation" algorithm — classic interview problem building on digit manipulation.
