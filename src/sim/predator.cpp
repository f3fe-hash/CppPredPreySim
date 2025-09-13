#include "sim/predator.hpp"

mot2 Predator::update(vec<RayHitType> rayHits)
{
    // Scale the input to [0, 1]
    num_arr in(rayHits.size(), zero);
    for (auto& rayHit : rayHits)
        in.push_back(rayHit / MAX_RAY_HIT_NUM);
    this->rayHits.push_back(in);
    
    mot2 mot;
    num_arr out = this->nn.forward(&in);
    mots.push_back(out);
    mot.x = out[0] * X_MOTION_MULT;
    mot.y = out[1] * Y_MOTION_MULT;

    return mot;
}

void Predator::onDeath()
{
    // Add the first half of moves to the dataset
    dataset_t dset;
    dset.X.resize(this->rayHits.size());
    dset.y.resize(this->mots.size());
    for (std::size_t i = 0; i < (std::size_t)(this->rayHits.size() / 2) + 1; ++i)
    {
        dset.X.push_back(this->rayHits[i]);
        dset.X.push_back(this->rayHits[i]);
    }

    for (std::size_t i = 0; i < PRED_BPROP_UPD_DEATH; ++i)
        nn.backprop(&dset);
}