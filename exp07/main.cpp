#include <iostream>
#include <vector>

using namespace std;

void LU_factorization(const vector<vector<double>>& A, const vector<double>& b, vector<double>& x) {
    int n = A.size();

    // Initialize L and U matrices
    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));

    // Set L to identity matrix
    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0;
    }

    // Perform LU factorization
    for (int k = 0; k < n; ++k) {
        for (int j = k; j < n; ++j) {
            double sum = 0.0;
            for (int p = 0; p < k; ++p) {
                sum += L[k][p] * U[p][j];
            }
            U[k][j] = A[k][j] - sum;
        }
        for (int i = k + 1; i < n; ++i) {
            double sum = 0.0;
            for (int p = 0; p < k; ++p) {
                sum += L[i][p] * U[p][k];
            }
            L[i][k] = (A[i][k] - sum) / U[k][k];
        }
    }

    // Solve Ly = b using forward substitution
    vector<double> y(n, 0);
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        for (int j = 0; j < i; ++j) {
            sum += L[i][j] * y[j];
        }
        y[i] = b[i] - sum;
    }

    // Solve Ux = y using backward substitution
    x.resize(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }
}

int main() {
    // Define the matrix A and vector b
    vector<vector<double>> A = {
            {2, 2, 2, 2},
            {3, 6, 9, 9},
            {1, 2, 4, 5},
            {2, 4, 8, 12}
    };

    vector<double> b = {0, -3, -2, -6};

    // Call the LU_factorization function
    vector<double> solution;
    LU_factorization(A, b, solution);

    // Print the solution
    cout << "Solution x: ";
    for (double val : solution) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
