#include <iostream>
#include <cmath>

double function_a(double x) {
    return 5 * x - cos(pow(x, 2) + 1);
}

double function_b(double x) {
    return cos(pow(x, 2) + 1) / 5;
}

std::pair<double, int> fixed_point_iteration(double initial_guess, double epsilon) {
    int iteration_count = 0;
    double x_current = initial_guess;
    double x_next;

    while (true) {
        x_next = function_b(x_current);

        if (std::abs(x_next - x_current) < epsilon) {
            return std::make_pair(x_next, iteration_count + 1);
        }

        x_current = x_next;
        iteration_count++;
    }
}

int main() {
    double initial_guess = 0.0;
    double epsilon = 0.00001;

    std::pair<double, int> result = fixed_point_iteration(initial_guess, epsilon);

    std::cout << "Root: " << result.first << std::endl;
    std::cout << "Iterations: " << result.second << std::endl;

    return 0;
}
