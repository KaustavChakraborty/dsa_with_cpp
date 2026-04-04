# String Reversal (Two-Pointer Technique)

A simple, efficient C++ implementation for reversing a string in-place. This approach uses the **Two-Pointer Technique**, which is a common pattern for solving array and string problems.

---

## 📝 Problem Statement
Given a string, reverse it without using extra memory for a second string. The modification must happen within the original memory space.

## ⚙️ How It Works
The algorithm uses two indices:
1. **Left Pointer:** Starts at the beginning of the string (index 0).
2. **Right Pointer:** Starts at the end of the string (index $n-1$).

In each step of a `while` loop, the characters at these two positions are swapped. The pointers then move toward each other until they meet or cross in the center.

### Performance
- **Time Complexity:** $O(N)$ — We visit each character at most once.
- **Space Complexity:** $O(1)$ — We only use two integer variables regardless of the input size.

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler (GCC/Clang/MSVC)

### Compilation
Save the code as `main.cpp` and run:
```bash
g++ main.cpp -o reverser
