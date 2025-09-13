#include "sim/prey.hpp"

Prey::Prey(std::shared_ptr<NeuralNetwork> nn)
{
    this->nn = nn;
}

mot2 Prey::update(const vec<RayHitType>* __restrict__ rayHits) noexcept
{
    // Scale the input to [0, 1]
    num_arr in(rayHits->size(), zero);
    for (auto rayHit : *rayHits)
        in.push_back(rayHit / MAX_RAY_HIT_NUM);
    this->rayHits.push_back(in);
    
    mot2 mot;
    num_arr out = this->nn->forward(&in);
    mots.push_back(out);
    mot.x = out[0] * X_MOTION_MULT;
    mot.y = out[1] * Y_MOTION_MULT;

    return mot;
}

void Prey::onDeath() noexcept
{
    // Add the first half of moves to the dataset
    dataset_t dset;
    dset.X.resize(this->rayHits.size());
    dset.y.resize(this->mots.size());
    for (std::size_t i = 0; i < (std::size_t)(this->rayHits.size() / 2) + 1; ++i)
    {
        dset.X.push_back(this->rayHits[i]);
        dset.y.push_back(this->mots[i]);
    }

    for (std::size_t i = 0; i < PREY_BPROP_UPD_DEATH; ++i)
        nn->backprop(&dset);
}