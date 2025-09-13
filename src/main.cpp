#include <memory> // For std::shared_ptr

// AIs
#include "ai/nn.hpp"
#include "sim/predator.hpp"
#include "sim/prey.hpp"

// Definitions and OpenGL
#include "sim/defs.hpp"
#include "sim/gl.hpp"

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
        prey.push_back(Prey(preyNN));

    // Populate predator vector
    preds.reserve(NUM_PREDS);
    for (i = 0; i < NUM_PREDS; ++i)
        preds.push_back(Predator(predNN));
    
    // Start the update loop
    context->start();

    // Cleanup OpenGL context
    delete context;
    return 0;
}

void update()
{}