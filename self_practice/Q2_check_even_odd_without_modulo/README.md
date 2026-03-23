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

---

## Time and Space Complexity

### All Methods
- **Time:** O(1) — single operation on a fixed-width integer, independent of the value of `n`.
- **Space:** O(1) — no data structures, no function calls, no heap allocation.

### Micro-performance Analysis (for hardware-aware interviews)
On x86-64 architecture:
- `n % 2` compiles to an `IDIV` or `AND` instruction depending on the compiler and optimization level. Modern compilers with `-O2` optimize `% 2` to a bitwise AND automatically, so the difference is often eliminated in optimized builds.
- `n & 1` always compiles to a single `AND` instruction — one clock cycle, no division unit required.
- For unoptimized builds (debug mode, `-O0`), `%` involves the integer division circuit (approximately 20–80 cycles on modern Intel CPUs, as the IDIV instruction has a high latency), while `& 1` is always one cycle.
- At simulation scale relevant to soft matter physics — e.g., checking parity for N=10⁹ lattice sites — this gap can translate to seconds of wall-clock time difference.

---

## Variations and Related Problems

### Variation 1 — Check Divisibility by Powers of 2
`n % 4 == 0` can be replaced with `(n & 3) == 0` (since 4-1=3=0b11). Generally: `n % (2^k) == 0` ↔ `(n & ((1 << k) - 1)) == 0`. This generalizes parity checking to any power-of-2 modulus.

### Variation 2 — Check if Exactly One of Two Numbers is Odd (XOR Parity)
`(a ^ b) & 1` — if the result is 1, exactly one of `a` or `b` is odd. This appears in toggle problems and signal processing.

### Variation 3 — Count Odd Numbers in Range [L, R] Without Looping
`(R - L) / 2 + (L % 2 != 0 ? 1 : 0)` or more cleanly: `(R + 1) / 2 - L / 2`. Tests mathematical reasoning over brute-force iteration.

### Variation 4 — Determine Parity of Number of Set Bits (Even/Odd Parity Bit)
`__builtin_parity(n)` returns 1 if the number of set bits is odd. This is used in error detection (parity bits in data transmission). The XOR-fold method: `x ^= x >> 16; x ^= x >> 8; x ^= x >> 4; x ^= x >> 2; x ^= x >> 1; result = x & 1`.

### Variation 5 — Alternate Array Elements (Even-index positive, Odd-index negative)
Uses parity of index `i & 1` to branch on sign assignment, placing this concept in an array-manipulation context.

---

## Key Interview Talking Points

- Knowing that `%` can return a negative value for negative operands in C++ is a genuine gotcha that catches many candidates off guard.
- Two's complement representation is the reason `& 1` works for negative numbers — this is worth stating explicitly to demonstrate understanding of how integers are stored.
- The compiler optimization point shows you think about the gap between source code and machine execution — valuable signal for a computational role.

---
