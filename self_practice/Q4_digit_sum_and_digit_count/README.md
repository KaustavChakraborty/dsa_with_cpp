# Digit Sum and Digit Count

## Problem Statement

Given a non-negative integer N (extend to handle negatives), compute:
1. The **sum of its digits** (digital root's precursor)
2. The **count of its digits**

Handle the edge case N = 0 explicitly (it has 1 digit with digit sum 0).

---

## Test Cases

| Test | Input | Digit Sum | Digit Count | Notes |
|------|-------|-----------|-------------|-------|
| TC1 | 0 | 0 | 1 | Edge case — zero has one digit |
| TC2 | 5 | 5 | 1 | Single digit |
| TC3 | 99 | 18 | 2 | Two nines |
| TC4 | 123 | 6 | 3 | Standard |
| TC5 | 9999 | 36 | 4 | All nines |
| TC6 | -456 | 15 | 3 | Negative — work on absolute value |
| TC7 | 1000000 | 1 | 7 | Sparse digits |
| TC8 | 2147483647 | 46 | 10 | INT_MAX |
| TC9 | 9876543210 | 45 | 10 | All digits 0-9 (use long long) |

---

## Algorithm Description

The algorithm leverages the two key integer operations:
- `n % 10` extracts the **last digit** (units position)
- `n / 10` removes the last digit (integer division by 10, shifting all digits right)

These two operations together allow iterating over each digit from right to left.

```
n = 4567

Iteration 1: digit = 4567 % 10 = 7,  sum += 7,  count++,  n = 456
Iteration 2: digit = 456  % 10 = 6,  sum += 6,  count++,  n = 45
Iteration 3: digit = 45   % 10 = 5,  sum += 5,  count++,  n = 4
Iteration 4: digit = 4    % 10 = 4,  sum += 4,  count++,  n = 0
Loop ends (n == 0)

sum = 7+6+5+4 = 22, count = 4
```

**Handling N = 0:** The while loop `while (n > 0)` doesn't execute for n=0, yielding sum=0, count=0. But 0 has one digit by convention, so we special-case it: output count=1, sum=0 before entering the loop.

**Handling negatives:** Apply `n = abs(n)` or `n = -n` before processing, since digits are defined for the magnitude only.

---

## Time and Space Complexity

**Time:** O(d) where d = number of digits in N = ⌊log₁₀(N)⌋ + 1.
- For a 32-bit integer (max 2,147,483,647), d ≤ 10. So practically O(1) for fixed-width integers.
- For a k-bit integer, d = O(k / log₂10) ≈ O(0.301k). So O(log N) in terms of the value of N.

**Space:** O(1) — constant number of variables (`temp`, `digitSum`, `digitCount`), no data structures.

**Alternative formula for digit count (O(1)):**
`count = (n == 0) ? 1 : (int)floor(log10(abs(n))) + 1`
This uses floating-point arithmetic and can have precision issues for numbers near exact powers of 10. The loop method is safer.

---

## Variations and Related Problems

### Variation 1 — Digital Root (Repeated Digit Sum)
Repeatedly sum the digits until a single digit remains.
- 9875 → 9+8+7+5 = 29 → 2+9 = 11 → 1+1 = 2
- Mathematical shortcut: `digital_root(n) = 1 + (n - 1) % 9` for n > 0. O(1) formula.
- Related to the divisibility rule for 9: a number is divisible by 9 iff its digital root is 9.

### Variation 2 — Product of Digits
Replace `sum +=` with `product *=` (initialize product to 1). Watch out: any 0 digit makes the product 0. Used in "multiplicative persistence" — how many times you multiply digits until a single digit remains.

### Variation 3 — Count Specific Digit Occurrences
Count how many times digit `d` appears in N. Add a condition: `if (digit == d) count++`. Extends to "how many times does digit 5 appear from 1 to N?" — a significantly harder problem requiring combinatorial counting.

### Variation 4 — Largest and Smallest Digit
Track `maxDigit` and `minDigit` while iterating. Used in number-reformatting problems (e.g., "form the largest number from digits of N").

### Variation 5 — Is N a Self-Describing Number?
A self-describing number N has the property that the digit at position i (0-indexed from left) equals the count of occurrences of digit i in N. E.g., 2020: position 0 has '2' → digit 0 appears twice ✓. Combines digit extraction with frequency counting.

### Variation 6 — Happy Number
Start with N. Replace N with the sum of squares of its digits. If you eventually reach 1, it's a Happy Number; if you enter a cycle, it's not. Uses digit sum extraction with cycle detection (Floyd's algorithm).

---
