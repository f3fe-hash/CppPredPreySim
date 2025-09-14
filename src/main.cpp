// For std::shared_ptr
#include <memory>

// AIs
#include "ai/nn.hpp"
#include "sim/predator.hpp"
#include "sim/prey.hpp"

// Definitions and OpenGL
#include "utils/defs.hpp"
#include "sim/gl.hpp"

// Math
#include "math/math.hpp"

std::shared_ptr<NeuralNetwork> predNN, preyNN;
GLContext* context;

vec<Predator> preds;
vec<Prey> prey;

int main(int argc, char** argv)
{
    // Initialize pointers
    context = new GLContext(argc, argv);

    // Create the neural networks
    predNN = std::make_shared<NeuralNetwork>(PRED_NET);
    preyNN = std::make_shared<NeuralNetwork>(PREY_NET);

    // Populate prey vector
    std::size_t i;
    prey.reserve(NUM_PREY);
    for (i = 0; i < NUM_PREY; ++i)
    {
        Prey _prey = Prey(preyNN);
        prey.push_back(_prey);
        objects.push_back({prey[i].getPos(), PREY, rand()});
    }

    // Populate predator vector
    preds.reserve(NUM_PREDS);
    for (i = 0; i < NUM_PREDS; ++i)
    {
        Predator pred = Predator(predNN);
        preds.push_back(pred);
        objects.push_back({preds[i].getPos(), PRED, rand()});
    }
    
    // Start the update loop
    context->start();

    // Cleanup OpenGL context
    delete context;
    return 0;
}

// Update AIs and non-graphics stuff
void update() noexcept
{
    vec<Object> objects2;
    objects2.reserve(NUM_PREY + NUM_PREDS);

    vec<RayHitType> hit;
    std::size_t i;
    for (i = 0; i < NUM_PREY; ++i)
    {
        hit = calcRayHitsPrey(objects[i], objects);
        (void) prey[i].update(&hit);
        objects2[i] = {prey[i].getPos(), PREY, objects[i].id};
    }

    // Access the objects after the prey
    for (std::size_t predIdx = 0; predIdx < NUM_PREDS; ++predIdx)
    {
        std::size_t objIdx = NUM_PREY + predIdx; // offset for predator objects in objects vector

        hit = calcRayHitsPred(objects[objIdx], objects);
        (void) preds[predIdx].update(&hit);
        objects2[objIdx] = {preds[predIdx].getPos(), PRED, objects[objIdx].id};
    }

    objects.clear();
    objects.swap(objects2);
}