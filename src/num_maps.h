#pragma once
#include <cstdint>


float large_to_normal(uint32_t n);
float large_to_signed_normal(uint32_t n);
float large_to_scalar(uint32_t n, float max_offset);

float bias_func(float x, float bias);

