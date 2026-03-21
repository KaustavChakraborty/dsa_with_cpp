# Swap Two Numbers (Without Temp Variable)

## Problem Statement

Given two integer variables `a` and `b`, exchange their values using three different techniques:
1. A temporary variable (baseline)
2. Arithmetic operators (addition and subtraction)
3. XOR bitwise operator

The core challenge of methods 2 and 3 is performing the swap **in-place** using only the two variables themselves, with zero additional memory allocation.

---

## Test Cases

| Test | Input | Expected Output | Notes |
|------|-------|-----------------|-------|
| TC1 | a=5, b=10 | a=10, b=5 | Basic positive integers |
| TC2 | a=0, b=7 | a=7, b=0 | Zero value |
| TC3 | a=-3, b=8 | a=8, b=-3 | Negative and positive |
| TC4 | a=-5, b=-9 | a=-9, b=-5 | Both negative |
| TC5 | a=42, b=42 | a=42, b=42 | Same values |
| TC6 | a=INT_MAX, b=1 | a=1, b=INT_MAX | Large values — arithmetic method overflows here |
| TC7 | a=INT_MIN, b=INT_MAX | a=INT_MAX, b=INT_MIN | Extreme values — XOR only safe method |

---

## Algorithm Description

### Method 1 — Temporary Variable
The canonical textbook approach. A third variable `temp` acts as a holding register. The value of `a` is saved into `temp`, `a` is overwritten with `b`, and then `b` is overwritten with the saved `temp`. Three assignment operations, one extra memory slot.

```
temp ← a
a    ← b
b    ← temp
```

### Method 2 — Arithmetic (Addition/Subtraction)
Encodes both values simultaneously in a single variable using their sum.

```
a ← a + b       (a now holds the sum S = a_orig + b_orig)
b ← a - b       (b = S - b_orig = a_orig)
a ← a - b       (a = S - a_orig = b_orig)
```

**Critical flaw:** If `a + b` exceeds `INT_MAX` or goes below `INT_MIN`, the result is **undefined behavior** for signed integers in C++. This method is only safe when you can guarantee no overflow — for instance, when both values are known to be small, or you use `long long` intermediaries.

### Method 3 — XOR Bitwise
Exploits the self-inverse property of XOR: `x ^ x = 0` and `x ^ 0 = x`.

```
a ← a ^ b       (a holds a_orig XOR b_orig, call it M)
b ← a ^ b       (b = M ^ b_orig = a_orig ^ b_orig ^ b_orig = a_orig)
a ← a ^ b       (a = M ^ a_orig = a_orig ^ b_orig ^ a_orig = b_orig)
```

**Critical flaw:** If `a` and `b` refer to the **same memory address** (aliasing — e.g., you pass the same pointer twice), then step 1 sets both to 0 (`x ^ x = 0`), permanently destroying the value. Always verify distinct addresses when using XOR swap on pointers.

---

## Time and Space Complexity

### Method 1
- **Time:** O(1) — exactly 3 assignments, each a single CPU operation.
- **Space:** O(1) — one extra variable `temp`, a single word on the stack.

### Method 2
- **Time:** O(1) — 3 arithmetic operations (+, -, -).
- **Space:** O(1) — zero extra variables. However, the CPU may use an internal register temporarily, which is still O(1).
- **Overflow note:** For two 32-bit integers, the sum could require 33 bits. Using `long long` as the accumulator resolves this at the cost of slightly wider instructions.

### Method 3
- **Time:** O(1) — 3 XOR operations. XOR is a single-cycle operation on all modern architectures.
- **Space:** O(1) — strictly zero extra memory. The bits of `a` and `b` themselves serve as the workspace.
- **In practice:** Modern compilers (GCC, Clang with `-O2`) generate identical or better assembly for all three methods. The XOR trick's performance advantage was real on 1970s–1980s hardware with constrained registers. Today it is a conceptual exercise.

---

## Variations and Related Problems

### Variation 1 — Swap Without Any Variable or Operator (Theoretical)
In some languages with destructuring assignment (`a, b = b, a` in Python), the swap is a language-level primitive. In C++, no equivalent exists, but you can achieve it via `std::swap(a, b)` from `<algorithm>`, which internally uses move semantics — relevant for non-primitive types.

### Variation 2 — Swap Two Variables of Different Types
Directly using the above methods fails when types differ (e.g., swapping a `float` and an `int`). You'd use `static_cast` to convert one type, swap, then cast back — introducing precision loss. This variation tests type awareness.

### Variation 3 — Swap Elements in an Array at Indices i and j
Generalizes the swap to work in-place within a data structure. This is the primitive operation underlying Bubble Sort, Selection Sort, and QuickSort's partition step. The aliasing danger of XOR swap is most practically relevant here: if `i == j`, the XOR swap destroys the element.

### Variation 4 — Swap Nibbles (Upper and Lower 4 Bits) of a Byte
`swapped = ((n & 0x0F) << 4) | ((n & 0xF0) >> 4)` — purely bitwise, single expression. Tests bit masking beyond simple XOR.

### Variation 5 — Swap Bits at Position i and j in an Integer
Check if bits at position i and j differ. If they do, flip both using XOR with a mask. If they are the same, no change needed. This generalizes the XOR swap concept to individual bit positions.

---

## Key Interview Talking Points

- **Why XOR swap is in interviews:** It tests bitwise operation fluency, not because it is practically superior. Knowing *when not to use it* (aliasing, non-integer types, modern compilers) is more impressive than just knowing the trick.
- **`std::swap` in production:** Always use `std::swap`. For user-defined types, it uses move semantics (C++11 and later), making it O(1) even for large objects by swapping internal pointers rather than copying data.
- **Undefined behavior:** The arithmetic method's overflow is undefined behavior for `signed int` in C++, not just implementation-defined. The compiler can assume it never happens and optimize away your safety checks — a subtle but real pitfall in C++.
