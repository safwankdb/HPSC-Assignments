#include <math.h>
#include <omp.h>

#include <chrono>
#include <iostream>
#include <random>

using namespace std;
using namespace std::chrono;

int main() {
    int time_taken;
    const int N = 100000000;
    const double a = -M_PI_2, b = M_PI_2;
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<double> dist(a, b);
    double I;
    for (int th = 2; th <= 8 && th << omp_get_max_threads(); th += 2) {
        auto start = high_resolution_clock::now();
        I = 0;
#pragma omp parallel for reduction(+ : I) num_threads(th)
        for (int i = 0; i < N; i++) {
            I += cos(dist(generator));
        }
        I *= (b - a) / N;
        auto stop = high_resolution_clock::now();
        time_taken = duration_cast<milliseconds>(stop - start).count();
        cout << "\nThreads = " << th << "\n\n\tSamples = " << N
             << "\n\tIntegral = " << I << "\n\tTime Elapsed = " << time_taken
             << " ms\n\n";
    }
    return 0;
}
