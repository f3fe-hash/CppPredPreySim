#pragma once

#include <vector>
#include <iostream>

#ifdef DEBUG
#include <cassert>
#endif

#define _debug(x) std::cout << "[DEBUG] " << x << std::endl;

template<typename T>
using vec = std::vector<T>;

template<typename T>
using vec2D = std::vector<std::vector<T>>;

using num       = float;
using num_arr   = vec<num>;
using num_arr2D = vec<num_arr>;

using score = double;

constexpr const num zero = (num)0.00;

struct dim2D
{
    std::size_t x;
    std::size_t y;
};

struct dataset_t
{
    vec<num_arr> X;
    vec<num_arr> y;

    std::size_t size;
};

struct dataset2D_t
{
    vec<num_arr2D> X;
    vec<num_arr2D> y;

    std::pair<std::size_t, std::size_t> dims;

    std::size_t size;
};