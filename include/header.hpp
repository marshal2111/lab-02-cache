// Copyright 2021 Your Name <your_email>
#include <chrono>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#define LINE_SIZE 16
#define MIN_CACHE_SIZE 32768
#define L1_CACHE_SIZE 65536
#define L2_CACHE_SIZE 262144
#define L3_CACHE_SIZE 1572864
#define MAX_CACHE_SIZE 2359296
#define EXP_NUM 5

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::nanoseconds ns;

void investigateCache();
auto example() -> void;

#endif // INCLUDE_HEADER_HPP_
