//Q1,a
#include <iostream>
#include <cmath>

double f(double y) {
    return 1.0 / (1 + y + y * y + pow(y, 4));
}

double trapezoidalRule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b)); // Add the first and last term

    for (int i = 1; i < n; ++i) {
        double y = a + i * h;
        sum += f(y);
    }

    return sum * h;
}

int main() {
    double a = 5.0, b = 10.0;
    int n = 1000000; // Number of intervals
    double result = trapezoidalRule(a, b, n);
    std::cout << "Integral from " << a << " to " << b << " is approximately: " << result << std::endl;

    return 0;
}


