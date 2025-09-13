#include <memory> // For std::shared_ptr

// AI
#include "ai/nn.hpp"

#include "sim/gl.hpp"
#include "sim/defs.hpp"

std::shared_ptr<NeuralNetwork> predNN, preyNN;

GLContext* context;

int main(int argc, char** argv)
{
    // Initialize pointers
    context = new GLContext(argc, argv);

    // Shared pointers
    predNN  = std::make_shared<NeuralNetwork>(PRED_NET);
    preyNN  = std::make_shared<NeuralNetwork>(PREY_NET);

    // Cleanup / Deallocate pointers
    delete context;
    return 0;
}