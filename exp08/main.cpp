#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

vector<double> Gauss_SeidelM(const vector<vector<double>>& A, const vector<double>& b, int N) {
    // Check if A is a square matrix
    int n = A.size();
    for (const auto& row : A) {
        if (row.size() != n) {
            throw invalid_argument("Matrix A must be square");
        }
    }

    // Check if the length of b matches the number of rows in A
    if (n != b.size()) {
        throw invalid_argument("Length of vector b must match the number of rows in matrix A");
    }

    // Initialize the solution vector x with zeros
    vector<double> x(n, 0.0);

    // Perform iterations
    for (int iter = 0; iter < N; ++iter) {
        for (int i = 0; i < n; ++i) {
            double sum1 = 0.0;
            for (int j = 0; j < i; ++j) {
                sum1 += A[i][j] * x[j];
            }
            double sum2 = 0.0;
            for (int j = i + 1; j < n; ++j) {
                sum2 += A[i][j] * x[j];
            }
            x[i] = (b[i] - sum1 - sum2) / A[i][i];
        }
    }

    return x;
}

int main() {
    // Define the coefficient matrix A and the constant vector b
    vector<vector<double>> A = {
            {5, -1, 3},
            {-2, 4, -1},
            {2, -2, 5}
    };

    vector<double> b = {14, 2, 10};

    // Set the number of iterations
    int N = 50;

    // Call the Gauss_SeidelM function
    vector<double> solution = Gauss_SeidelM(A, b, N);

    // Print the solution
    cout << "Solution using Gauss-Seidel method: ";
    for (double val : solution) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
