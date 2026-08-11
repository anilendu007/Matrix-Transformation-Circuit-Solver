#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdexcept>

// Solves Ax = b matrix loops using partial pivoting Gaussian Elimination from scratch
std::vector<double> custom_gaussian_solver(std::vector<std::vector<double>> A, std::vector<double> b) {
    int n = A.size();

    // 1. Construct the Augmented Matrix [A | b]
    for (int i = 0; i < n; ++i) {
        A[i].push_back(b[i]);
    }

    // 2. Forward Elimination Loop
    for (int i = 0; i < n; ++i) {
        // Partial Pivoting: Locate the largest element in column i for numeric stability
        int max_row = i;
        for (int r = i + 1; r < n; ++r) {
            if (std::abs(A[r][i]) > std::abs(A[max_row][i])) {
                max_row = r;
            }
        }

        // Structural check for singular (degenerate/unsolvable) circuit systems
        if (std::abs(A[max_row][i]) < 1e-12) {
            throw std::runtime_error("Mathematical Error: System matrix is singular (degenerate network).");
        }

        // Swap current row with the optimal pivot row pointers
        std::swap(A[i], A[max_row]);

        // Eliminate elements below the current active diagonal pivot
        for (int row = i + 1; row < n; ++row) {
            double factor = A[row][i] / A[i][i];
            for (int col = i; col <= n; ++col) {
                A[row][col] -= factor * A[i][col];
            }
        }
    }

    // 3. Back Substitution Phase to isolate loop current variables
    std::vector<double> solution(n, 0.0);
    for (int i = n - 1; i >= 0; --i) {
        solution[i] = A[i][n] / A[i][i];
        for (int row = i - 1; row >= 0; --row) {
            A[row][n] -= A[row][i] * solution[i];
        }
    }

    return solution;
}

int main() {
    // Models a 3-loop Kirchhoff's Voltage Law (KVL) resistance mesh grid array
    // Formulated System: R_mesh * I_mesh = V_sources
    
    // R_mesh: Connected interaction branch resistances (expressed in Ohms)
    std::vector<std::vector<double>> R_mesh = {
        {15.0, -5.0,  0.0},
        {-5.0, 20.0, -10.0},
        {0.0, -10.0,  12.0}
    };
    
    // V_sources: Vector representing independent electrical source potentials (Volts)
    std::vector<double> V_sources = {10.0, 0.0, -5.0};

    try {
        std::vector<double> current_vectors = custom_gaussian_solver(R_mesh, V_sources);
        
        std::cout << "==================================================================\n";
        std::cout << "      ECE COGNITIVE COMPUTATION: LINEAR ALGEBRA CIRCUIT SOLVER     \n";
        std::cout << "==================================================================\n";
        std::cout << std::fixed << std::setprecision(4);
        
        for (size_t idx = 0; idx < current_vectors.size(); ++idx) {
            std::cout << "Mesh Loop Current I" << (idx + 1) << ": " << current_vectors[idx] << " Amperes\n";
        }
        std::cout << "==================================================================\n";
    } 
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
