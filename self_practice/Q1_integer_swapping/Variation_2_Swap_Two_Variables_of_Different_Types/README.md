README: Cross-Type Variable Swapping in C++
Overview

In standard C++, the std::swap function requires both arguments to be of the same type. This project explores a manual swap between an int and a float. While the logic follows the traditional "temporary variable" pattern, the fundamental difference in how these types store data leads to information entropy.
The Mechanism

The swap is performed in three distinct steps to ensure the compiler respects the memory boundaries of each variable:

    Promotion: The int is promoted to a float and stored in a temporary buffer.

    Demotion (The Bottleneck): The float is cast to an int. This is where the fractional part is truncated.

    Assignment: The buffered value is assigned to the float variable.

Technical Discussion: The "Information Leak"

When swapping variables of different types, we encounter three primary issues that are critical in computational physics and high-precision R&D:
1. Precision Loss (Truncation)

Floating-point numbers (IEEE 754) represent real numbers, while integers represent discrete steps.

    Observation: When 3.14f is swapped into an int, the .14 is not rounded; it is truncated.

    Result: The value 3.14 becomes 3. In iterative simulations (like Monte Carlo or Molecular Dynamics), this "small" loss can lead to significant numerical drift.

2. The static_cast vs. C-Style Cast

This implementation utilizes static_cast<type>(variable).

    Safety: Unlike C-style casts (int)b, static_cast is checked by the compiler. It prevents accidental bit-reinterpretation and makes the "intentional" loss of data visible to other developers.

    Clarity: It explicitly signals that the developer is aware that a conversion—and possible data degradation—is occurring.

3. Range and Overflow Risks

    Integer Limits: A 32-bit int maxes out at approximately 2.1×109.

    Float Limits: A float can represent magnitudes up to ≈3.4×1038.

    Risk: If b were a large scientific value (e.g., 1.5×1012), swapping it into a would cause an integer overflow, resulting in undefined behavior or a wrapped-around negative value.
