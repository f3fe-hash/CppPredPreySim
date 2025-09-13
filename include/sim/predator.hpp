#pragma once

#include "ai/nn.hpp"
#include "sim/defs.hpp"

class Predator
{
    NeuralNetwork& nn;
    vec<num_arr> mots;
    vec<num_arr> rayHits;
public:
    Predator(NeuralNetwork& nn);
    ~Predator();

    mot2 update(vec<RayHitType> rayHits);

    void onDeath();
};
