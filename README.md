# Linear Algebra Engine & Multi-Loop Circuit Solver

A library-free, performance-optimized C++ engine that models complex physical networks as simultaneous linear systems ($Ax = b$) and solves them via Gaussian Elimination with Partial Pivoting.

## Engineering Architecture
- `include/matrix_solver.hpp` & `src/matrix_solver.cpp`: Implements a specialized matrix solver designed for row-major cache locality, featuring partial pivoting to mitigate floating-point truncation errors.
- `include/circuit.hpp` & `src/circuit.cpp`: Maps physical system dynamics (Kirchhoff's Voltage Law) directly into bounded matrix layouts.
- `src/main.cpp`: Entry execution program building and tracking an arbitrarily structured multi-loop mesh topology.
- `CMakeLists.txt`: Build-system automation applying strict optimization flags (`-O3`) to achieve minimal pipeline latency.

## Algorithmic & Hardware Optimization Details
1. **Numerical Stability**: Standard Gaussian Elimination suffers from precision failure if a diagonal element is close to zero. This engine implements **Partial Pivoting**, tracking down column values to swap the optimal absolute-weight row dynamically.
2. **Memory Alignment & Cache Utilization**: Matrix traversals inside inner computational loops are organized along structural row dimensions matching standard C++ row-major packing. This minimizes cache eviction overhead.
3. **Zero Deep-Copy Overhead**: Large tracking fields are transferred down operational chains natively utilizing either `const` references or explicit rvalue moving semantics (`std::move`).

## Building the Executable
Compile using standard tools supporting **C++17** and **CMake**:

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
./circuit_solver
```



### 🏎️ Cache Locality & Structural Benchmarks
* **Memory Flattening:** Rewrote the multi-dimensional layout into a contiguous, 1D flattened array schema, maximizing spatial locality and triggering automated compiler loop unrolling.
* **Pivoting Efficiency:** Replaced runtime row-swapping pointer moves with a tracking vector framework, dropping algorithm tracking overhead during numerical scaling stress tests.
* **Keywords Used:** `1D Flattened Arrays`, `Cache Line Alignment`, `Spatial Locality Optimization`, `Partial Pivoting Stability`, `Compiler Loop Unrolling`.
