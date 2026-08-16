#include "circuit.hpp"
#include "matrix_solver.hpp"
#include <stdexcept>

namespace quant_eng {

CircuitSolver::CircuitSolver(size_t num_loops) 
    : num_loops_(num_loops), 
      resistance_matrix_(num_loops * num_loops, 0.0), 
      voltage_vector_(num_loops, 0.0) {}

void CircuitSolver::configure_loop(size_t loop_idx, const MeshLoop& loop_config) {
    if (loop_idx >= num_loops_) {
        throw std::out_of_bounds("Loop index exceeds pre-allocated matrix size.");
    }

    // Self-resistance forms the primary diagonal element
    resistance_matrix_[loop_idx * num_loops_ + loop_idx] = loop_config.total_resistance;
    
    // Shared mutual resistances form symmetric off-diagonal elements (Negative mutual terms in KVL)
    for (const auto& [neighbor_idx, resistance] : loop_config.shared_resistances) {
        if (neighbor_idx >= num_loops_) {
            throw std::invalid_argument("Neighboring loop index is out of system bounds.");
        }
        resistance_matrix_[loop_idx * num_loops_ + neighbour_idx] = -resistance;
    }

    voltage_vector_[loop_idx] = loop_config.total_voltage_source;
}

std::vector<double> CircuitSolver::calculate_currents() const {
    // Create local modifiable copies since our solver optimizes using in-place modifications
    std::vector<double> A_copy = resistance_matrix_;
    std::vector<double> b_copy = voltage_vector_;

    return MatrixSolver::solve_linear_system(A_copy, b_copy, num_loops_);
}

} // namespace quant_eng
