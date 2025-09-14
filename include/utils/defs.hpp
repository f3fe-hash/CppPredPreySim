#pragma once

#include <iostream>
#include <vector>
#include <cstdarg>

#ifdef DEBUG
#include <cassert>
#endif

#define _debug(x) std::cout << "[DEBUG] " << x << std::endl;

#define _wur    __attribute__((warn_unused_result))
#define _pure   __attribute__((pure))
#define _const  __attribute__((const))
#define _unused __attribute__((unused))

#define _nonnull(...) __attribute__((nonnull (__VA_ARGS__)))

/* -----------------------
 * Type definitions.
 * ----------------------- */

template<typename T>
using vec = std::vector<T>;

template<typename T>
using vec2D = std::vector<std::vector<T>>;

using num       = float;
using num_arr   = vec<num>;
using num_arr2D = vec<num_arr>;

using score = double;

// Type of object the ray hit
enum RayHitType
{
    NONE = 0,
    PRED = 1,
    PREY = 2
};

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

// Object
struct Object
{
    dim2 centerPos;
    RayHitType type;

    int id;
};

struct dim2D
{
    std::size_t x;
    std::size_t y;
};

struct dataset_t
{
    vec<num_arr> X;
    vec<num_arr> y;

    std::size_t size;
};

struct dataset2D_t
{
    vec<num_arr2D> X;
    vec<num_arr2D> y;

    std::pair<std::size_t, std::size_t> dims;

    std::size_t size;
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

constexpr const num zero = (num)0.00;