
# Matrix Transformation & Circuit Solver

A clean, library-free engine that models multi-loop electrical circuits as linear systems and solves for currents using a custom **Gaussian Elimination** algorithm.

## 🚀 Key Features
* **Zero Dependencies:** Written purely from scratch using 2D arrays.
* **Mesh Analysis Engine:** Converts circuit loop equations directly into (R*I = V) matrices.
* **Custom Row Reduction:** Implements O(n³) forward elimination and back substitution.
* **Edge-Case Safety:** Built-in checks to prevent division-by-zero errors during matrix pivots.

## How It Works

This system utilizes Kirchhoff's Voltage Law (KVL) to represent complex multi-loop circuit networks into clean matrix structures:

$$R \cdot I = V$$

$$
\begin{bmatrix} R_{11} & R_{12} & R_{13} \\ R_{21} & R_{22} & R_{23} \\ R_{31} & R_{32} & R_{33} \end{bmatrix} \begin{bmatrix} I_1 \\ I_2 \\ I_3 \end{bmatrix} = \begin{bmatrix} V_1 \\ V_2 \\ V_3 \end{bmatrix}
$$

Where:
* $R$ = Matrix of interconnected loop resistances (Ohms)
* $I$ = Vector of unknown target mesh currents to isolate (Amperes)
* $V$ = Vector of fixed loop source voltage potentials (Volts)



## 💻 Sample Output
```text
Input Matrix [R | V]:
[  10.0  -2.0  -4.0 |  12.0 ]
[  -2.0   8.0  -1.0 |   0.0 ]
[  -4.0  -1.0   6.0 |  -6.0 ]

Solving...

Results:
Loop 1 Current (I1) =  1.34 A
Loop 2 Current (I2) =  0.45 A
Loop 3 Current (I3) = -0.03 A
```

## 🛠️ Tech Stack
* **Language:** C / C++
* **Concepts:** 2D Arrays, Multidimensional Pointers, Linear Algebra

---
**Author:** Riya Tiwari (1st Sem ECE Student)
