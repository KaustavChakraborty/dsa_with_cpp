# Fibonacci Sequence — First N Terms

## Problem Statement

Print the first N terms of the Fibonacci sequence, defined by:
- F(0) = 0
- F(1) = 1
- F(n) = F(n-1) + F(n-2) for n ≥ 2

Implement using both `for` and `while` loops. Handle invalid input (N ≤ 0). Choose data types that prevent premature overflow.

---

## Test Cases

| Test | Input N | Expected Output | Notes |
|------|---------|-----------------|-------|
| TC1 | 1 | 0 | Single term |
| TC2 | 2 | 0 1 | Two terms |
| TC3 | 7 | 0 1 1 2 3 5 8 | Classic check |
| TC4 | 10 | 0 1 1 2 3 5 8 13 21 34 | Standard |
| TC5 | 0 | Error message | Invalid input |
| TC6 | -5 | Error message | Negative input |
| TC7 | 20 | Last term: 4181 | Fits in int |
| TC8 | 46 | Last term: 1134903170 | Last term fitting in 32-bit signed int |
| TC9 | 47 | Last term: 1836311903+... | Overflows int; needs long long |
| TC10 | 93 | Last term: 12200160415121876738 | Last term fitting in unsigned long long |

---

## Algorithm Description

The iterative Fibonacci algorithm maintains two variables, `prev` and `curr`, representing F(n-1) and F(n) respectively. In each iteration, it computes the next Fibonacci number as their sum, then slides the window forward: `prev` takes the old `curr` value, `curr` takes the new sum.

```
State: (prev=0, curr=1)

Step 1: output prev=0, next=0+1=1, state becomes (prev=1, curr=1)
Step 2: output prev=1, next=1+1=2, state becomes (prev=1, curr=2)
Step 3: output prev=1, next=1+2=3, state becomes (prev=2, curr=3)
Step 4: output prev=2, next=2+3=5, state becomes (prev=3, curr=5)
...
```

The `for` and `while` loop implementations are algorithmically identical — the difference is purely syntactic. The `for` loop is preferred when the iteration count is known ahead of time (cleaner, all loop control in one line). The `while` loop is preferred when the termination condition is more complex or state-dependent.

**Why `long long` instead of `int`:**
Fibonacci numbers grow exponentially — approximately as φⁿ/√5 where φ ≈ 1.618 (the golden ratio). F(46) = 1,836,311,903 which is within `int` range (max ~2.1 billion), but F(47) = 2,971,215,073 which exceeds it. `long long` extends safe computation to F(92) before overflow. Beyond that, you need arbitrary-precision arithmetic (BigInteger).

---

## Time and Space Complexity

### Iterative (Both `for` and `while`)
- **Time:** O(N) — exactly N iterations, one addition per iteration.
- **Space:** O(1) — only two variables (`prev`, `curr`) regardless of N. No array, no recursion stack.

### Why Not Recursive?
A naive recursive implementation — `fib(n) = fib(n-1) + fib(n-2)` — has:
- **Time:** O(2ⁿ) — exponential, because it recomputes the same subproblems repeatedly. `fib(5)` computes `fib(3)` twice, `fib(2)` three times, etc.
- **Space:** O(N) — recursion call stack depth equals N.

For N=50, the naive recursive approach makes ~2⁵⁰ ≈ 10¹⁵ function calls. At 10⁹ calls/second, that's over 11 days of computation for a problem that iteratively solves in microseconds.

### Memoized Recursion (Top-Down DP)
- **Time:** O(N) — each subproblem computed once.
- **Space:** O(N) — memo table (array or hash map) of size N.

### Matrix Exponentiation (Advanced)
The identity `[F(n+1), F(n); F(n), F(n-1)] = [[1,1],[1,0]]^n` allows computing F(N) in O(log N) time using fast matrix exponentiation — relevant when N is astronomically large (e.g., N = 10¹⁸).

---

## Variations and Related Problems

### Variation 1 — Find Nth Fibonacci Without Storing Sequence
Same as the iterative approach but only return the Nth value rather than printing all N. Still O(N) time, O(1) space.

### Variation 2 — Check if a Number is a Fibonacci Number
A positive integer N is a Fibonacci number if and only if one (or both) of `5N² + 4` or `5N² - 4` is a perfect square. This gives an O(1) membership test after computing the square root.

### Variation 3 — Fibonacci Modulo M (Pisano Period)
For cryptography and competitive programming, `F(N) % M` is needed for very large N. The Fibonacci sequence modulo M is periodic (Pisano period π(M)). Computing π(M) allows reducing N modulo π(M) before computing, solving even N=10¹⁸ efficiently.

### Variation 4 — Generalized Fibonacci (Tribonacci, k-step)
T(n) = T(n-1) + T(n-2) + T(n-3) with T(0)=0, T(1)=0, T(2)=1. Requires tracking k previous values instead of 2. Generalizes to any k-step recurrence.

### Variation 5 — Fibonacci Search Algorithm
An alternative to binary search using Fibonacci numbers to split the search space. Useful when random memory access is expensive (tape drives, certain cache hierarchies).

### Variation 6 — Zeckendorf's Theorem
Every positive integer can be represented uniquely as a sum of non-consecutive Fibonacci numbers. Finding this representation is a greedy algorithm. Relevant to number theory and data encoding.

---

## Key Interview Talking Points

- The jump from O(2ⁿ) to O(N) by converting recursive to iterative is a canonical example of dynamic programming (memoization / tabulation). Interviewers use Fibonacci as the entry point to DP conversations.
- Mentioning the golden ratio growth rate (φⁿ) and the consequent overflow behavior shows mathematical depth.
- If asked "how would you compute F(10¹⁸)?", the answer is matrix exponentiation with modular arithmetic — connecting to fast exponentiation (Problem I12).

---
