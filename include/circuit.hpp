#pragma once
#include <vector>
#include <string>

namespace quant_eng {

struct MeshLoop {
    std::string name;
    double total_resistance;
    std::vector<std::pair<size_t, double>> shared_resistances; // {neighbor_index, resistance}
    double total_voltage_source;                               // Net voltage driving the loop
};

class CircuitSolver {
public:
    explicit CircuitSolver(size_t num_loops);
    
    void configure_loop(size_t loop_idx, const MeshLoop& loop_config);
    std::vector<double> calculate_currents() const;

private:
    size_t num_loops_;
    std::vector<double> resistance_matrix_;
    std::vector<double> voltage_vector_;
};

} // namespace quant_eng
