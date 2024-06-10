#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
// Function to minimize
double f(double x1, double x2) {
    return -x1 * x2;
}

// Constraint function
double g(double x1, double x2) {
    return x1 + x2 - 2;
}

// Objective function with penalty term
double q(double x1, double x2, double ck) {
    return f(x1, x2) + ck * pow(g(x1, x2), 2);
}

int main() {
    double x1 = 1, x2 = 1;
    double ck = 1.0;
    double tol = 1e-6;
    double prev_result = INFINITY;

    vector<double> results;

    while (true) {
        results.push_back(q(x1, x2, ck));

        // Stopping criterion
        if (abs(prev_result - q(x1, x2, ck)) / (abs(prev_result) + numeric_limits<double>::epsilon()) < tol) {
            break;
        }

        // Update previous result
        prev_result = q(x1, x2, ck);

        // Increase penalty parameter
        ck *= 10;
    }

    // Output results
    double final_f = f(x1, x2);
    cout << "Final solution: x1 = " << x1 << ", x2 = " << x2 << ", f(x1, x2) = " << final_f << endl;
    cout << "Results at each step: ";
    for (double result : results) {
        cout << result << " ";
    }
    cout << endl;

    return 0;
}
