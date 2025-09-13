#include <iostream>
#include <iomanip>

#include "ai/nn.hpp"
#include "sim/defs.hpp"

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    
    NeuralNetwork predNN = NeuralNetwork(PRED_NET);
    NeuralNetwork preyNN = NeuralNetwork(PREY_NET);

    return 0;
}