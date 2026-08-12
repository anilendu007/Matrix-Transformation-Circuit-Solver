#include "matrix_solver.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>

namespace quant_eng {

std::vector<double> MatrixSolver::solve_linear_system(std::vector<std::vector<double>> A, std::vector<double> b) {
    size_t n = A.size();
    if (n == 0 || b.size() != n) {
        throw std::invalid_argument("Matrix dimensions must match vector dimensions.");
    }

    // 1. Forward Elimination with Partial Pivoting (Maintains numerical precision)
    for (size_t i = 0; i < n; ++i) {
        // Find the pivot row with the max absolute value in the current column (Cache optimization)
        size_t max_row = i;
        for (size_t k = i + 1; k < n; ++k) {
            if (std::abs(A[k][i]) > std::abs(A[max_row][i])) {
                max_row = k;
            }
        }

        // Swap rows in A and b if a larger pivot element is found
        if (max_row != i) {
            std::swap(A[i], A[max_row]);
            std::swap(b[i], b[max_row]);
        }

        // Check for singularity or ill-conditioned matrix
        if (std::abs(A[i][i]) < EPSILON) {
            throw std::runtime_error("Matrix is singular or near-singular. System cannot be solved cleanly.");
        }

        // Eliminate entries down the column row-by-row (Row-major layout preserves memory locality)
        for (size_t k = i + 1; k < n; ++k) {
            double factor = A[k][i] / A[i][i];
            for (size_t j = i; j < n; ++j) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    // 2. Back Substitution
    std::vector<double> x(n, 0.0);
    for (int i = static_cast<int>(n) - 1; i >= 0; --i) {
        double sum = b[i];
        for (size_t j = static_cast<size_t>(i) + 1; j < n; ++j) {
            sum -= A[i][j] * x[j];
        }
        x[static_cast<size_t>(i)] = sum / A[i][i];
    }

    return x;
}

} // namespace quant_eng
