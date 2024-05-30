#include <cmath>
#include <windows.h>

extern "C" __declspec(dllexport) const char* getFunctionName() {
    return "cos^2(x)";
}

typedef void (*CallbackType)(int messageType, double x, double fx, double Fx, double delta);

double factorial(int n) {
    return (n == 0 || n == 1) ? 1 : n * factorial(n - 1);
}

double binom(int n) {
    return pow(-1, n + 1) * (pow(2, 2 * n - 1));
}

double series_cos2(double x, double epsilon, CallbackType callback) {
    double term, sum = 0.0;
    int n = 1;
    double prev_sum;
    do {
        prev_sum = sum;
        term = binom(n) * pow(x, 2 * n) / factorial(2 * n);
        sum += term;
        double F = pow(cos(x), 2);
        double delta = sqrt(fabs(pow(sum, 2) - pow(F, 2)));
        callback(1, x, sum, F, delta);
        n++;
    } while (fabs(sum - prev_sum) >= epsilon);
    return sum;
}

extern "C" __declspec(dllexport) void calculate(double x_start, double x_end, double dx, double epsilon, CallbackType callback) {
    for (double x = x_start; x <= x_end; x += dx) {
        series_cos2(x, epsilon, callback);
    }
}
