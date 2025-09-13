#pragma once

#include <vector>
#include <cstdarg>

#define _wur    __attribute__((warn_unused_result))
#define _pure   __attribute__((pure))
#define _unused __attribute__((unused))

#define _nonnull(...) __attribute__((nonnull (__VA_ARGS__)))

/* -----------------------
 * Type definitions.
 * ----------------------- */

 // Vector
template<typename T>
using vec = std::vector<T>;

// Dimenions
struct dim2
{
    std::size_t x, y;
};

// Motion
struct mot2
{
    std::size_t x, y;
};

// Type of object the ray hit
enum RayHitType
{
    NONE = 0,
    PRED = 1,
    PREY = 2
};

/* -----------------------
 * Constants
 * ----------------------- */

// Maximum number in RayHitType. Used to
// scale the ray hit type to 0 - 1 in the nn.
#define MAX_RAY_HIT_NUM 2

// Predator config
#define PRED_SIZE            25
#define PRED_VIEW_DIST       200
#define PRED_RAY_ANGLE_DIFF  3
#define PRED_RAY_SAMPLE_NUM  20
#define PRED_BPROP_UPD_DEATH 10 // Number of backpropagation updates to do upon death of a predator

// Prey config
#define PREY_SIZE            25
#define PREY_VIEW_DIST       75
#define PREY_RAY_ANGLE_DIFF  3
#define PREY_RAY_SAMPLE_NUM  20
#define PREY_BPROP_UPD_DEATH 10 // Number of backpropagation updates to do upon death of a prey

// Number of prey and predators
#define NUM_PREDS 10
#define NUM_PREY  50

// Motion multipliers
#define X_MOTION_MULT 5
#define Y_MOTION_MULT 5

// 800x600 window
const dim2 SIM_WINDOW_SIZE = {800, 600};

// Predator neural network
const vec<std::size_t> PRED_NET{PRED_RAY_SAMPLE_NUM, 10, 2};
const vec<std::size_t> PREY_NET{PREY_RAY_SAMPLE_NUM, 10, 2};