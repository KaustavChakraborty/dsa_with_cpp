# B2 — Check Even/Odd Without Modulo

## Problem Statement

Determine whether a given integer is even or odd using three approaches:
1. The standard modulo operator `%`
2. Bitwise AND with 1 (`& 1`)
3. Ternary operator shorthand

The deeper challenge embedded in this problem is understanding *why* the bitwise approach is valid — connecting binary representation to mathematical parity — and being able to articulate the performance implications.

---

## Test Cases

| Test | Input | Expected | Notes |
|------|-------|----------|-------|
| TC1 | 0 | Even | Zero edge case — zero is even by definition |
| TC2 | 1 | Odd | Smallest positive odd |
| TC3 | -4 | Even | Negative even |
| TC4 | -7 | Odd | Negative odd |
| TC5 | INT_MAX (2147483647) | Odd | 2^31 - 1 is odd |
| TC6 | INT_MIN (-2147483648) | Even | -2^31 is even |
| TC7 | 1000000000 | Even | Large even number |

---

## Algorithm Description

### Method 1 — Modulo
`n % 2 == 0` computes the remainder of integer division by 2. If the remainder is 0, the number is even; if 1 (or -1 for negative numbers in C++), it is odd.

**Note on negative numbers and `%` in C++:** In C++11 and later, the result of `a % b` has the same sign as `a` (truncation toward zero). So `-7 % 2 == -1`, not `1`. The condition `n % 2 == 0` still correctly identifies evens, but `n % 2 == 1` fails for negative odd numbers — you must write `n % 2 != 0`.

### Method 2 — Bitwise AND with 1
Every integer in binary representation stores its value in positional powers of 2. The **least significant bit (LSB)** — bit position 0 — contributes a value of 2⁰ = 1 if set. Since every even number is a sum of powers of 2 starting from 2¹, even numbers always have their LSB equal to 0. Odd numbers always have LSB equal to 1.

```
Decimal 6  = 0b00000110 → LSB = 0 → Even
Decimal 7  = 0b00000111 → LSB = 1 → Odd
Decimal -4 = 0b...11100 (two's complement) → LSB = 0 → Even
Decimal -7 = 0b...11001 (two's complement) → LSB = 1 → Odd
```

`n & 1` isolates only the LSB. The result is 0 (even) or 1 (odd), regardless of sign, because two's complement preserves the LSB's parity meaning.
