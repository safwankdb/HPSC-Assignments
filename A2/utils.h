#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#define vf vector<float>
#define vvf vector<vector<float>>

using namespace std;

void print(vvf &M) {
    cout << endl;
    cout.setf(ios::fixed);
    for (vf row : M) {
        cout << '\t';
        for (float i : row) cout << setw(10) << setprecision(2) << i << " ";
        cout << endl;
    }
    cout << endl;
    return;
}

float randomFloat() {
    static mt19937 generator(42);
    static uniform_real_distribution<double> dist(-2, 2);
    return dist(generator);
}
