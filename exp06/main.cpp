#include <iostream>
#include <cmath>
#include <vector>

// Define the function to perform Trapezoid Rule integration
double Trapezoid_Uniform(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double result = 0.5 * (f(a) + f(b)); // Initialize result with endpoints

    for (int i = 1; i < n; ++i) {
        result += f(a + i * h);
    }

    return h * result;
}

// Define the function to perform Simpson's Rule integration
double Simpson_Uniform(double (*f)(double), double a, double b, int n) {
    if (n % 2 != 0) {
        throw std::invalid_argument("Number of subintervals (n) must be even for Simpson's Rule.");
    }

    double h = (b - a) / n;
    double result = f(a) + f(b); // Initialize result with endpoints

    for (int i = 1; i < n; i += 2) {
        result += 4 * f(a + i * h);
    }

    for (int i = 2; i < n - 1; i += 2) {
        result += 2 * f(a + i * h);
    }

    return h / 3 * result;
}

// Define the function to perform Gauss Quadrature Rule integration
double Gauss_Quadrature_Rule(double (*f)(double), double a, double b, int n) {
    std::vector<double> nodes(n + 1);
    std::vector<double> weights(n + 1);

    // Calculate nodes and weights using Legendre polynomial
    for (int i = 0; i <= n; ++i) {
        nodes[i] = cos(M_PI * (i + 0.75) / (n + 0.5));
        double p0 = 1.0;
        double p1 = nodes[i];
        double p2;
        for (int j = 1; j <= 30; ++j) {
            p2 = ((2 * j + 1) * nodes[i] * p1 - j * p0) / (j + 1);
            p0 = p1;
            p1 = p2;
        }
        weights[i] = 2.0 / ((1 - nodes[i] * nodes[i]) * p2 * p2);
    }

    double result = 0.0;
    for (int i = 0; i <= n; ++i) {
        result += weights[i] * f(0.5 * (b - a) * nodes[i] + 0.5 * (b + a));
    }
    result *= 0.5 * (b - a);

    return result;
}

// Define the functions to be integrated
double f1(double x) {
    return sin(2 * x);
}

double f2(double x) {
    return 2 * x - 2;
}

double f3(double x) {
    return 2 * x * x * x + x * x;
}

int main() {
    // Set the intervals
    std::vector<std::pair<double, double>> intervals = {{0, M_PI}, {-2, 1}, {-3, 1}};

    // Values of n to test
    std::vector<int> n_values = {2, 4, 10, 20, 50, 100};

    // Test functions using Trapezoid Rule, Simpson's Rule, and Gauss Quadrature Rule
    for (int n : n_values) {
        std::cout << "Results for n = " << n << ":" << std::endl;
        for (int i = 0; i < intervals.size(); ++i) {
            double trapezoid_result = Trapezoid_Uniform(f1, intervals[i].first, intervals[i].second, n);
            double simpson_result = Simpson_Uniform(f1, intervals[i].first, intervals[i].second, n);
            double gauss_result = Gauss_Quadrature_Rule(f1, intervals[i].first, intervals[i].second, n);
            std::cout << "f" << i+1 << ": Trapezoid = " << trapezoid_result << ", Simpson's = " << simpson_result << ", Gauss Quadrature = " << gauss_result << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
