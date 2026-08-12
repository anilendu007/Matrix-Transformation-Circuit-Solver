#pragma once
#include <vector>

namespace quant_eng {

class MatrixSolver {
public:
    // Solves Ax = b using Gaussian Elimination with Partial Pivoting to eliminate round-off error
    // Uses pass-by-value because the algorithm modifies the matrix in-place during elimination
    static std::vector<double> solve_linear_system(
        std::vector<std::vector<double>> A, 
        std::vector<double> b
    );

private:
    static constexpr double EPSILON = 1e-9; // Threshold to catch singular matrices / division-by-zero
};

} // namespace quant_eng
