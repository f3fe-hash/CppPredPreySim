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

    dim2 pos;
public:
    explicit Prey(std::shared_ptr<NeuralNetwork> nn) noexcept;
    ~Prey() = default;

    _nonnull(1)
    mot2 update(const vec<RayHitType>* __restrict__ rayHits) noexcept;

    void onDeath() noexcept;

    _pure
    inline std::size_t getX() noexcept
    {return this->pos.x;}

    _pure
    inline std::size_t getY() noexcept
    {return this->pos.y;}

    _pure
    inline dim2 getPos() noexcept
    {return this->pos;}
};
