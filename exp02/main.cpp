#include <iostream>
#include <cmath>

// problem 3 - c
double bisection(double (*f)(double), double a, double b, double epsilon) {
    double mid = a + (b - a) / 2;
    while (std::abs(f(mid)) >= epsilon) {
        if (f(a) * f(mid) < 0)
            b = mid;
        else
            a = mid;
        mid = (a + b) / 2;
    }
    return mid;
}

double f1(double x) {
    return std::exp(x) - 6 * x;
}

double f2(double x) {
    return 1 / x - std::tan(x);
}

double bisec(double a, double b, double (*f)(double)) {
    double mid = (a + b) / 2;
    if (std::abs(a - b) < 1e-4)
        return mid;
    if (f(a) * f(mid) < 0)
        return bisec(a, mid, f);
    else
        return bisec(mid, b, f);
}

int main() {
    double epsilon = 1e-6;
    double a, b;

    // problem 3
    a = 0; b = 1;
    std::cout << "Problem 3: " << bisection(f1, a, b, epsilon) << std::endl;

    a = 2; b = 4;
    std::cout << "Problem 3: " << bisection(f1, a, b, epsilon) << std::endl;

    // problem 5
    a = 0.1; b = M_PI / 3;
    std::cout << "Problem 5: " << bisec(a, b, f2) << std::endl;

    // problem 6
    double seq_a[30] = {2};
    double seq_b[30] = {2};
    double seq_c[30] = {1, 2};

    int n_0 = 30;
    for (int i = 1; i < n_0; ++i) {
        double a = seq_a[i - 1] - 1 + 2 / std::exp(seq_a[i - 1]);
        seq_a[i] = a;
        std::cout << "seq_a[" << i << "]: " << seq_a[i] << std::endl;
    }

    for (int i = 1; i < n_0; ++i) {
        double b = seq_b[i - 1] + 1 / 5.0 - std::exp(seq_b[i - 1]) / 10.0;
        seq_b[i] = b;
        std::cout << "seq_b[" << i << "]: " << seq_b[i] << std::endl;
    }

    for (int i = 2; i < n_0; ++i) {
        double c = seq_c[i - 1] - ((seq_c[i - 1] - seq_c[i - 2]) / (std::exp(seq_c[i - 1]) - std::exp(seq_c[i - 2]))) * (std::exp(seq_c[i - 1] - 2));
        seq_c[i] = c;
        std::cout << "seq_c[" << i << "]: " << seq_c[i] << std::endl;
    }

    return 0;
}
