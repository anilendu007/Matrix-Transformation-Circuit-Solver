#include "circuit.hpp"
#include "matrix_solver.hpp"
#include <stdexcept>

namespace quant_eng {

CircuitSolver::CircuitSolver(size_t num_loops) 
    : num_loops_(num_loops), 
      resistance_matrix_(num_loops, std::vector<double>(num_loops, 0.0)), 
      voltage_vector_(num_loops, 0.0) {}

void CircuitSolver::configure_loop(size_t loop_idx, const MeshLoop& loop_config) {
    if (loop_idx >= num_loops_) {
        throw std::out_of_bounds("Loop index exceeds pre-allocated matrix size.");
    }

    // Self-resistance forms the primary diagonal element
    resistance_matrix_[loop_idx][loop_idx] = loop_config.total_resistance;
    
    // Shared mutual resistances form symmetric off-diagonal elements (Negative mutual terms in KVL)
    for (const auto& [neighbor_idx, resistance] : loop_config.shared_resistances) {
        if (neighbor_idx >= num_loops_) {
            throw std::invalid_argument("Neighboring loop index is out of system bounds.");
        }
        resistance_matrix_[loop_idx][neighbor_idx] = -resistance;
    }

    voltage_vector_[loop_idx] = loop_config.total_voltage_source;
}

std::vector<double> CircuitSolver::calculate_currents() const {
    // Forward mapping directly to the specialized numerical elimination solver
    return MatrixSolver::solve_linear_system(resistance_matrix_, voltage_vector_);
}

} // namespace quant_eng
