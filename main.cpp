#include <iostream>
#include <cmath>


int main() {
    auto a = new float[1024];
    auto b = new float[1024];
    std::fill(&a[0], &a[1024], 1);
    std::fill(&b[0], &b[1024], 1);
#pragma omp target map(tofrom: b[0:1024]) map(to: a[0:1024])
#pragma omp teams distribute parallel for default(none) shared(a, b)
    for (int i = 0; i < 1024; ++i) {
        b[i] = a[i] * a[i] + b[i] * b[i];
    }
    float x = 0;
#pragma omp target map(tofrom: x) map(to: b[0:1024])
#pragma omp teams distribute reduction(+:x) default(none) shared(b)
    for (int i = 0; i < 1024; ++i) {
        x += b[i];
    }
    std::cout << x << std::endl;
    return 0;
}
