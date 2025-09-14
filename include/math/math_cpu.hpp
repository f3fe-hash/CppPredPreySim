#pragma once

#include <vector>
#include <cmath>

#include "utils/defs.hpp"

constexpr const double PI         = 3.14592653;
constexpr const double DEG_TO_RAD = PI / 180.0;

_const
inline num mult_add(const num_arr& a, const num_arr& b, const num c, std::size_t n) noexcept
{
#ifdef DEBUG
    assert(a.size() == b.size());
    assert(a.size() == n);
#endif
    num sum = zero;
    for (std::size_t i = 0; i < n; ++i)
        sum += a[i] * b[i];
    return sum + c;
}

_const
inline num_arr activation(const num_arr a, std::size_t n) noexcept
{
    num_arr arr = num_arr(n);
    for (std::size_t i = 0; i < n; i++)
        arr[i] = (num)(1 / (1 + std::exp((double)-a[i])));
    return arr;
}

_const
inline num_arr activation_derv(const num_arr a, std::size_t n) noexcept
{
    num_arr arr = num_arr(n);
    for (std::size_t i = 0; i < n; i++)
        arr[i] = a[i] * (1 - a[i]);
    return arr;
}

_const
inline num_arr error(const num_arr x, const num_arr y, std::size_t n) noexcept
{
    num_arr arr = num_arr(n);
    for (std::size_t i = 0; i < n; i++)
        arr[i] = x[i] - y[i];
    return arr;
}

// Calculate what the rays cast from a predator hits.
_const
inline vec<RayHitType> calcRayHitsPred(Object obj, vec<Object> objects) noexcept
{
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
                Object _obj = objects[k];

                // The id probably isn't the predator's id, but it might be.
                if (__builtin_expect(obj.id == _obj.id, false))
                    continue;

                const double abs_y = abs((double)y);
                const double abs_x = abs((double)x);
                constexpr int pred_size_2 = PRED_SIZE / 2;
                constexpr int prey_size_2 = PREY_SIZE / 2;
                if (_obj.type == PRED)
                {
                    if (abs_y > abs((double)_obj.centerPos.y - pred_size_2) ||
                        abs_y > abs((double)_obj.centerPos.y + pred_size_2) ||
                        abs_x > abs((double)_obj.centerPos.x - pred_size_2) ||
                        abs_x > abs((double)_obj.centerPos.x + pred_size_2))
                    {
                        hits[i] = PRED;
                        _break = true;
                        break;
                    }
                }
                else if (_obj.type == PREY)
                {
                    if (abs_y > abs((double)_obj.centerPos.y - prey_size_2) ||
                        abs_y > abs((double)_obj.centerPos.y + prey_size_2) ||
                        abs_x > abs((double)_obj.centerPos.x - prey_size_2) ||
                        abs_x > abs((double)_obj.centerPos.x + prey_size_2))
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
_const
inline vec<RayHitType> calcRayHitsPrey(Object obj, vec<Object> objects) noexcept
{
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
                Object _obj = objects[k];

                // The id probably isn't prey's id, but it might be.
                if (__builtin_expect(obj.id == _obj.id, false))
                    continue;
                
                const double abs_y = abs((double)y);
                const double abs_x = abs((double)x);
                constexpr int pred_size_2 = PRED_SIZE / 2;
                constexpr int prey_size_2 = PREY_SIZE / 2;
                if (_obj.type == PRED)
                {
                    if (abs_y > abs((double)_obj.centerPos.y - pred_size_2) ||
                        abs_y > abs((double)_obj.centerPos.y + pred_size_2) ||
                        abs_x > abs((double)_obj.centerPos.x - pred_size_2) ||
                        abs_x > abs((double)_obj.centerPos.x + pred_size_2))
                    {
                        hits[i] = PRED;
                        _break = true;
                        break;
                    }
                }
                else if (_obj.type == PREY)
                {
                    if (abs_y > abs((double)_obj.centerPos.y - prey_size_2) ||
                        abs_y > abs((double)_obj.centerPos.y + prey_size_2) ||
                        abs_x > abs((double)_obj.centerPos.x - prey_size_2) ||
                        abs_x > abs((double)_obj.centerPos.x + prey_size_2))
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