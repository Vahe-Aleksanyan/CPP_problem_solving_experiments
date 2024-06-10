#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Define the objective function
double f(const vector<double>& x) {
    return pow(x[0]*x[0] + 1, 2) + x[1]*x[1];
}

// Define the gradient of the objective function
vector<double> grad_f(const vector<double>& x) {
    return {4*x[0]*(pow(x[0]*x[0] + 1, 2)), 2*x[1]};
}

// Armijo backtracking algorithm with fixed initial step size
double armijo_line_search(const vector<double>& x, const vector<double>& grad, double alpha_init = 1.0, double beta = 0.5, double sigma = 1e-4) {
    double alpha = alpha_init;
    while (f({x[0] - alpha * grad[0], x[1] - alpha * grad[1]}) > f(x) - sigma * alpha * (grad[0] * grad[0] + grad[1] * grad[1])) {
        alpha *= beta;
    }
    return alpha;
}

// Gradient descent with Armijo backtracking line search
pair<vector<double>, int> gradient_descent_armijo(const vector<double>& x0, double epsilon) {
    vector<double> x = x0;
    int k = 0;
    while (sqrt(grad_f(x)[0] * grad_f(x)[0] + grad_f(x)[1] * grad_f(x)[1]) > epsilon) {
        vector<double> grad = grad_f(x);
        double alpha = armijo_line_search(x, grad);
        x[0] -= alpha * grad[0];
        x[1] -= alpha * grad[1];
        k++;
    }
    return {x, k};
}

int main() {
    // Initial point
    vector<double> x0 = {25, 20};
    // Stopping criterion
    double epsilon = 1e-3;

    // Perform gradient descent with Armijo backtracking line search
    pair<vector<double>, int> result = gradient_descent_armijo(x0, epsilon);
    vector<double> x_armijo = result.first;
    int k_armijo = result.second;

    // Print results
    cout << "Armijo Backtracking:" << endl;
    cout << "Minimum point: [" << x_armijo[0] << ", " << x_armijo[1] << "]" << endl;
    cout << "Number of iterations: " << k_armijo << endl;

    return 0;
}
