#include "num_maps.h"
#include <cmath>


float large_to_normal(uint32_t n) {
    return (float)((double)(n % 100000) / 100000.0);
}

float large_to_signed_normal(uint32_t n) {
    return 2.f * large_to_normal(n) - 1.f;
}

float large_to_scalar(uint32_t n, float max_offset) {
    const float scale = 1.f + max_offset * large_to_normal(n);
    if (n % 2 == 0) {
        return scale;
    } else {
        return 1.f / scale;
    }
}


float bias_func(float x, float bias) {
    const float k = std::pow(1.f - bias, 3.f);
    return (x * k) / (x * k - x + 1);
}
