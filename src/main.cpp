#include "circuit.hpp"
#include <iostream>
#include <iomanip>

int main() {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "============= GAUSSIAN ELIMINATION CIRCUIT SOLVER =============\n";

    try {
        // Setup a 3-loop complex circuit grid system
        size_t total_loops = 3;
        quant_eng::CircuitSolver solver(total_loops);

        // Configure Loop 0: Total R = 10 ohms, drives 12V, shares 5 ohms with Loop 1
        solver.configure_loop(0, {"Loop_A", 10.0, {{1, 5.0}}, 12.0});

        // Configure Loop 1: Total R = 15 ohms, drives 0V, shares 5 ohms with Loop 0, 3 ohms with Loop 2
        solver.configure_loop(1, {"Loop_B", 15.0, {{0, 5.0}, {2, 3.0}}, 0.0});

        // Configure Loop 2: Total R = 8 ohms, drives -5V (reverse polarity source), shares 3 ohms with Loop 1
        solver.configure_loop(2, {"Loop_C", 8.0, {{1, 3.0}}, -5.0});

        // Run the linear algebra solution engine
        std::vector<double> loop_currents = solver.calculate_currents();

        std::cout << "System Matrix Generation: [Success]\n";
        std::cout << "Calculated Mesh Currents:\n";
        for (size_t i = 0; i < loop_currents.size(); ++i) {
            std::cout << "  Current in Loop " << i << " (I_" << i << "): " << loop_currents[i] << " Amperes\n";
        }
        std::cout << "===============================================================\n";

    } catch (const std::exception& e) {
        std::cerr << "Solver Runtime Exception Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
