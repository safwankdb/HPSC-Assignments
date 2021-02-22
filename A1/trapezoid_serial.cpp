#include <math.h>

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main() {
    int time_taken;
    const int N = 100000000;
    const double a = -M_PI_2, b = M_PI_2;
    double del_x = (b - a) / N, I;
    auto start = high_resolution_clock::now();
    I = (cos(b) + cos(a)) / 2;
    for (int i = 0; i < N; i++) {
        I += cos(a + (i + 1) * del_x);
    }
    I *= del_x;
    auto stop = high_resolution_clock::now();
    time_taken = duration_cast<milliseconds>(stop - start).count();
    cout << "\n\tDivisions = " << N << "\n\tIntegral = " << I
         << "\n\tTime Elapsed = " << time_taken << " ms\n\n";
    return 0;
}
