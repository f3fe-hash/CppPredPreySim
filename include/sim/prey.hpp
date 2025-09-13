#pragma once

// For std::shared_ptr
#include <memory>

#include "ai/nn.hpp"
#include "sim/defs.hpp"

class Prey
{
    std::shared_ptr<NeuralNetwork> nn;

    vec<num_arr> mots;
    vec<num_arr> rayHits;
public:
    explicit Prey(std::shared_ptr<NeuralNetwork> nn);
    ~Prey() = default;

    _nonnull(1)
    mot2 update(const vec<RayHitType>* __restrict__ rayHits) noexcept;

    void onDeath() noexcept;
};
