#pragma once

#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "ai/utils/defs.hpp"
#include "ai/math/math.hpp"

class NeuralNetwork
{
    num_arr2D delta;
    num_arr2D layer_outputs;
    num_arr2D biases;
    vec<num_arr2D> weights;

    vec<std::size_t> layer_sizes;

    std::random_device rd{};
    std::mt19937       gen;

    double lr      = 0.05;
    int batch_size = 1;

public:
    explicit NeuralNetwork(vec<std::size_t> layer_sizes) noexcept;
    ~NeuralNetwork() = default;

    num_arr forward(const num_arr* input) noexcept;

    void backprop(const dataset_t* dset) noexcept;
};