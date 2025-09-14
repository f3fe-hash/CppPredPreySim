// For std::shared_ptr
#include <memory>

#include <cmath>

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

vec<RayHitType> calcRayHitsPred(Object obj) noexcept;
vec<RayHitType> calcRayHitsPrey(Object obj) noexcept;

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
        hit = calcRayHitsPrey(objects[i]);
        (void) prey[i].update(&hit);
        objects2[i] = {prey[i].getPos(), PREY, objects[i].id};
    }

    // Access the objects after the prey
    for (std::size_t predIdx = 0; predIdx < NUM_PREDS; ++predIdx)
    {
        std::size_t objIdx = NUM_PREY + predIdx; // offset for predator objects in objects vector

        hit = calcRayHitsPred(objects[objIdx]);
        (void) preds[predIdx].update(&hit);
        objects2[objIdx] = {preds[predIdx].getPos(), PRED, objects[objIdx].id};
    }

    objects.clear();
    objects.swap(objects2);
}

// Calculate what the rays cast from a predator hits.
inline vec<RayHitType> calcRayHitsPred(Object obj) noexcept
{
    constexpr const double DEG_TO_RAD = 3.141592653 / 180.0;

    vec<RayHitType> hits(PRED_RAY_SAMPLE_NUM);
    for (std::size_t i = 0; i < PRED_RAY_SAMPLE_NUM; ++i)
    {
        // Calculate the slope at the requested angle
        const double slope = std::tan((i - (PRED_RAY_SAMPLE_NUM / 2)) * PRED_RAY_ANGLE_DIFF * DEG_TO_RAD);
        for (std::size_t x = obj.centerPos.x; x <= obj.centerPos.x + PRED_VIEW_DIST; ++x)
        {
            bool _break = false;
            const double y = x * slope + obj.centerPos.y;
            for (std::size_t k = 0; k < objects.size(); ++k)
            {
                // The id probably isn't the scanning object's id,
                // but it might be.
                if (__builtin_expect(obj.id == objects[k].id, false))
                    continue;

                const double abs_y = abs((double)y);
                const double abs_x = abs((double)x);
                constexpr int pred_size_2 = PRED_SIZE / 2;
                constexpr int prey_size_2 = PREY_SIZE / 2;
                if (objects[k].type == PRED)
                {
                    if (abs_y > abs((double)objects[k].centerPos.y - pred_size_2) ||
                        abs_y > abs((double)objects[k].centerPos.y + pred_size_2) ||
                        abs_x > abs((double)objects[k].centerPos.x - pred_size_2) ||
                        abs_x > abs((double)objects[k].centerPos.x + pred_size_2))
                    {
                        hits[i] = PRED;
                        _break = true;
                        break;
                    }
                }
                else if (objects[k].type == PREY)
                {
                    if (abs_y > abs((double)objects[k].centerPos.y - prey_size_2) ||
                        abs_y > abs((double)objects[k].centerPos.y + prey_size_2) ||
                        abs_x > abs((double)objects[k].centerPos.x - prey_size_2) ||
                        abs_x > abs((double)objects[k].centerPos.x + prey_size_2))
                    {
                        hits[i] = PREY;
                        _break = true;
                        break;
                    }
                }
            }

            if (_break)
                break;
        }
    }

    return hits;
}

// Calculate what the rays cast from a prey hits.
inline vec<RayHitType> calcRayHitsPrey(Object obj) noexcept
{
    constexpr const double DEG_TO_RAD = 3.141592653 / 180.0;

    vec<RayHitType> hits(PREY_RAY_SAMPLE_NUM);
    for (std::size_t i = 0; i < PREY_RAY_SAMPLE_NUM; ++i)
    {
        // Calculate the slope at the requested angle
        const double slope = std::tan((i - (PREY_RAY_SAMPLE_NUM / 2)) * PREY_RAY_ANGLE_DIFF * DEG_TO_RAD);
        for (std::size_t x = obj.centerPos.x; x <= obj.centerPos.x + PREY_VIEW_DIST; ++x)
        {
            bool _break = false;
            const double y = x * slope + obj.centerPos.y;
            for (std::size_t k = 0; k < objects.size(); ++k)
            {
                const double abs_y = abs((double)y);
                const double abs_x = abs((double)x);
                constexpr int pred_size_2 = PRED_SIZE / 2;
                constexpr int prey_size_2 = PREY_SIZE / 2;
                if (objects[k].type == PRED)
                {
                    if (abs_y > abs((double)objects[k].centerPos.y - pred_size_2) ||
                        abs_y > abs((double)objects[k].centerPos.y + pred_size_2) ||
                        abs_x > abs((double)objects[k].centerPos.x - pred_size_2) ||
                        abs_x > abs((double)objects[k].centerPos.x + pred_size_2))
                    {
                        hits[i] = PRED;
                        _break = true;
                        break;
                    }
                }
                else if (objects[k].type == PREY)
                {
                    if (abs_y > abs((double)objects[k].centerPos.y - prey_size_2) ||
                        abs_y > abs((double)objects[k].centerPos.y + prey_size_2) ||
                        abs_x > abs((double)objects[k].centerPos.x - prey_size_2) ||
                        abs_x > abs((double)objects[k].centerPos.x + prey_size_2))
                    {
                        hits[i] = PREY;
                        _break = true;
                        break;
                    }
                }
            }

            if (_break)
                break;
        }
    }

    return hits;
}