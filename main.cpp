#include <iostream>
#include <cmath>
__attribute__((noinline)) void add(float (&a)[1024], float (&b)[1024]) {
#pragma omp target map(tofrom:b[0:1024]) map(to:a[0:1024])
#pragma omp teams distribute parallel for default(none) shared(a, b)
    for (int i = 0; i < 1024; ++i) {
        b[i] = ::sqrtf(a[i] * a[i] + b[i] * b[i]);
    }
}

int main() {
    float a[1024] = {1};
    std::fill(&a[0], &a[1024], 1);
    float b[1024] = {1};
    std::fill(&b[0], &b[1024], 1);
    for (int i = 0; i < 1000; ++i) {
        add(a, b);
    }
    for (float i: b) {
        std::cout << i << std::endl;
    }
    return 0;
}
