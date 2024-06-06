#include <iostream>
#include <vector>
#include <cmath>  // For exp function and mathematical constants

// Function prototype for the bisection method (iterative version)
double bisection(double (*f)(double), double a, double b, double epsilon);

// Function prototype for the bisection method (recursive version)
double bisec(double (*f)(double), double a, double b, double epsilon);

// Define the function f1(x) = exp(x) - 6 * x
double f1(double x) {
    return std::exp(x) - 6 * x;
}

// Define the function f2(x) = 1/x - tan(x)
double f2(double x) {
    return (1 / x) - std::tan(x);
}

// Function to generate and analyze sequence A
void generateSequenceA(int n0, double initial) {
    std::vector<double> seq_a = {initial};

    for (int i = 1; i < n0; ++i) {
        double a = seq_a[i - 1] - 1 + 2 / std::exp(seq_a[i - 1]);
        seq_a.push_back(a);
        double abserr = std::abs(seq_a[i] - seq_a[i - 1]);
        std::cout << "Seq_A [" << i << "] = " << seq_a[i] << "  Abserr = " << abserr << std::endl;
    }
}

// Function to generate and analyze sequence B
void generateSequenceB(int n0, double initial) {
    std::vector<double> seq_b = {initial};

    for (int i = 1; i < n0; ++i) {
        double b = seq_b[i - 1] + 1.0 / 5.0 - (std::exp(seq_b[i - 1]) / 10.0);
        seq_b.push_back(b);
        double abserr = std::abs(seq_b[i] - seq_b[i - 1]);
        std::cout << "Seq_B [" << i << "] = " << seq_b[i] << "  Abserr = " << abserr << std::endl;
    }
}

// Function to generate and analyze sequence C
void generateSequenceC(int n0, double initial1, double initial2) {
    std::vector<double> seq_c = {initial1, initial2};

    for (int i = 2; i < n0; ++i) {
        double c = seq_c[i - 1] - ((seq_c[i - 1] - seq_c[i - 2]) /
                                   (std::exp(seq_c[i - 1]) - std::exp(seq_c[i - 2]))) *
                                  std::exp(seq_c[i - 1] - 2);
        seq_c.push_back(c);
        double abserr = std::abs(seq_c[i] - seq_c[i - 1]);
        std::cout << "Seq_C [" << i << "] = " << seq_c[i] << "  Abserr = " << abserr << std::endl;
    }
}

int main() {
    double epsilon = 1e-6;

    // First interval for f1 in [0, 1]
    double a1 = 0.0;
    double b1 = 1.0;
    std::cout << "Root of f1 in interval [0, 1]: " << bisection(f1, a1, b1, epsilon) << std::endl;

    // Second interval for f1 in [2, 4]
    double a2 = 2.0;
    double b2 = 4.0;
    std::cout << "Root of f1 in interval [2, 4]: " << bisection(f1, a2, b2, epsilon) << std::endl;

    // Interval for f2 in [0.1, pi/3]
    double a3 = 0.1;
    double b3 = M_PI / 3;  // M_PI is the value of π from <cmath>
    double epsilon_rec = 1e-4;  // Different epsilon for the recursive function

    std::cout << "Root of f2 in interval [0.1, pi/3]: " << bisec(f2, a3, b3, epsilon_rec) << std::endl;

    int n0 = 30;
    std::cout << "\nGenerating and analyzing sequences up to " << n0 << " terms:\n" << std::endl;

    // Sequence A generation and analysis
    std::cout << "Sequence A Analysis:" << std::endl;
    generateSequenceA(n0, 2.0);

    // Sequence B generation and analysis
    std::cout << "\nSequence B Analysis:" << std::endl;
    generateSequenceB(n0, 2.0);

    // Sequence C generation and analysis
    std::cout << "\nSequence C Analysis:" << std::endl;
    generateSequenceC(n0, 1.0, 2.0);

    return 0;
}

// Iterative bisection method implementation for f1
double bisection(double (*f)(double), double a, double b, double epsilon) {
    double mid = a + (b - a) / 2;

    while (std::abs(f(mid)) >= epsilon) {
        if (f(a) * f(mid) < 0) {
            b = mid;
        } else {
            a = mid;
        }
        mid = (a + b) / 2;
    }

    return mid;
}

// Recursive bisection method implementation for f2
double bisec(double (*f)(double), double a, double b, double epsilon) {
    double mid = (a + b) / 2;

    if (std::abs(a - b) < epsilon) {
        return mid;
    }

    if (f(a) * f(mid) < 0) {
        return bisec(f, a, mid, epsilon);
    } else {
        return bisec(f, mid, b, epsilon);
    }
}
