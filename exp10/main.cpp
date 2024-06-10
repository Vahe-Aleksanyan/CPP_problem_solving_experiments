#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

// Helper function to run gradient descent
void run_gradient_descent(double X[], double Y[], double theta[], double step_size, int iterations, int m, int n) {
    for (int iter = 0; iter < iterations; ++iter) {
        double* gradients = new double[n]();

        // Compute the gradients
        for (int i = 0; i < m; ++i) {
            double prediction = 0.0;
            for (int j = 0; j < n; ++j) {
                prediction += theta[j] * X[i * n + j];
            }
            double error = prediction - Y[i];
            for (int j = 0; j < n; ++j) {
                gradients[j] += error * X[i * n + j];
            }
        }

        // Update the parameters
        for (int j = 0; j < n; ++j) {
            theta[j] -= (step_size / m) * gradients[j];
        }

        delete[] gradients;

        // Debugging output
        if ((iter + 1) % 10 == 0) { // Adjust the frequency of output as needed
            std::cout << "Iteration " << iter + 1 << ", Theta: ";
            for (int j = 0; j < n; ++j) {
                std::cout << theta[j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

// Helper function to run stochastic gradient descent
void run_stochastic_gradient_descent(double X[], double Y[], double theta[], double step_size, int iterations, int m, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, m - 1);

    for (int iter = 0; iter < iterations; ++iter) {
        for (int i = 0; i < m; ++i) {
            int index = dis(gen);
            double prediction = 0.0;
            for (int j = 0; j < n; ++j) {
                prediction += theta[j] * X[index * n + j];
            }
            double error = prediction - Y[index];
            for (int j = 0; j < n; ++j) {
                theta[j] -= step_size * error * X[index * n + j];
            }
        }

        // Debugging output
        if ((iter + 1) % 10 == 0) { // Adjust the frequency of output as needed
            std::cout << "Iteration " << iter + 1 << ", Theta: ";
            for (int j = 0; j < n; ++j) {
                std::cout << theta[j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    // Define data and parameters
    int m = 100; // Number of samples
    int n = 2;   // Number of features
    double* X = new double[m * n]; // Features
    double* Y = new double[m];     // Labels
    double learning_rate = 0.001;  // Smaller learning rate
    int iterations = 100;
    double* theta = new double[n];
    for (int i = 0; i < n; ++i) {
        theta[i] = 0;
    }

    // Initialize X and Y with your data...
    std::default_random_engine generator;
    std::normal_distribution<double> noise(0.0, 0.1);

    for (int i = 0; i < m; ++i) {
        X[i * n + 0] = i / 100.0; // Scale the feature
        X[i * n + 1] = 1;
        Y[i] = (3.0 * X[i * n + 0] + 2.0) + noise(generator); // Y = 3X + 2 + noise
    }

    // Step sizes to test
    std::vector<double> step_sizes = {0.0005, 0.0001, 0.00003, 0.00001, 0.000003, 0.000001};

    // Comparing Gradient Descent and Stochastic Gradient Descent
    for (double step_size : step_sizes) {
        std::cout << "Step size: " << step_size << std::endl;

        // Gradient Descent
        double* theta_gd = new double[n];
        std::copy(theta, theta + n, theta_gd);
        run_gradient_descent(X, Y, theta_gd, step_size, iterations, m, n);

        // Stochastic Gradient Descent
        double* theta_sgd = new double[n];
        std::copy(theta, theta + n, theta_sgd);
        run_stochastic_gradient_descent(X, Y, theta_sgd, step_size, iterations, m, n);

        // Output results
        std::cout << "Gradient Descent Theta: ";
        for (int i = 0; i < n; ++i) {
            std::cout << theta_gd[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Stochastic Gradient Descent Theta: ";
        for (int i = 0; i < n; ++i) {
            std::cout << theta_sgd[i] << " ";
        }
        std::cout << std::endl;

        delete[] theta_gd;
        delete[] theta_sgd;
    }

    delete[] X;
    delete[] Y;
    delete[] theta;

    return 0;
}
