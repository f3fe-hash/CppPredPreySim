#pragma once

#include <vector>
#include <cmath>

#include "ai/utils/defs.hpp"

__attribute__((const))
#ifdef DEBUG
inline num mult_add(const num_arr& a, const num_arr& b, const num c, std::size_t n)
#else
inline num mult_add(const num_arr& a, const num_arr& b, const num c, std::size_t n) noexcept
#endif
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

__attribute__((const))
#ifdef DEBUG
inline num_arr activation(const num_arr a, std::size_t n)
#else
inline num_arr activation(const num_arr a, std::size_t n) noexcept
#endif
{
    num_arr arr = num_arr(n);
    for (std::size_t i = 0; i < n; i++)
        arr[i] = (num)(1 / (1 + std::exp((double)-a[i])));
    return arr;
}

__attribute__((const))
#ifdef DEBUG
inline num_arr activation_derv(const num_arr a, std::size_t n)
#else
inline num_arr activation_derv(const num_arr a, std::size_t n) noexcept
#endif
{
    num_arr arr = num_arr(n);
    for (std::size_t i = 0; i < n; i++)
        arr[i] = a[i] * (1 - a[i]);
    return arr;
}

__attribute__((const))
#ifdef DEBUG
inline num_arr error(const num_arr x, const num_arr y, std::size_t n)
#else
inline num_arr error(const num_arr x, const num_arr y, std::size_t n) noexcept
#endif
{
    num_arr arr = num_arr(n);
    for (std::size_t i = 0; i < n; i++)
    {
        arr[i] = x[i] - y[i];
    }
    return arr;
}

/*---------------------------*
 * 2D math functions
 *---------------------------*/

__attribute__((const))
#ifdef DEBUG
inline num_arr mult_add2D(const num_arr2D& a, const num_arr2D& b, const num_arr& c, std::size_t n)
#else
inline num_arr mult_add2D(const num_arr2D& a, const num_arr2D& b, const num_arr& c, std::size_t n) noexcept
#endif
{
#ifdef DEBUG
    _debug(std::string("a.size() = ") << a.size());
    _debug(std::string("b.size() = ") << b.size());
    _debug(std::string("c.size() = ") << c.size());
    _debug(std::string("n        = ") << n);
    assert(a.size() == b.size());
    assert(b.size() == c.size());
    assert(c.size() == n);
#endif

    num_arr sum = num_arr(n);
    for (std::size_t i = 0; i < n; ++i)
    {
#ifdef DEBUG
        _debug(std::string("a[i].size() = ") << a[i].size());
        _debug(std::string("b[i].size() = ") << b[i].size());
        assert(a[i].size() == b[i].size());
#endif
        for (std::size_t j = 0; j < a[i].size(); ++j)
            sum[i] += a[i][j] * b[i][j];
        sum[i] += c[i];
    }

    return sum;
}

__attribute__((const))
#ifdef DEBUG
inline num_arr2D activation2D(const num_arr2D a, std::size_t n)
#else
inline num_arr2D activation2D(const num_arr2D a, std::size_t n) noexcept
#endif
{
#ifdef DEBUG
    assert(a.size() == n);
#endif

    num_arr2D arr = num_arr2D(n);
    for (std::size_t i = 0; i < n; ++i)
    {
        arr[i].resize(a[i].size());
        for (std::size_t j = 0; j < a[i].size(); ++j)
            arr[i][j] = (num)(1 / (1 + std::exp((double)-a[i][j])));
    }

    return arr;
}

__attribute__((const))
#ifdef DEBUG
inline num_arr2D activation_derv2D(const num_arr2D a, std::size_t n)
#else
inline num_arr2D activation_derv2D(const num_arr2D a, std::size_t n) noexcept
#endif
{
#ifdef DEBUG
    assert(a.size() == n);
#endif

    num_arr2D arr = num_arr2D(n);
    for (std::size_t i = 0; i < n; ++i)
    {
        arr[i].resize(a[i].size());
        for (std::size_t j = 0; j < a[i].size(); ++j)
            arr[i][j] = a[i][j] * (1 - a[i][j]);
    }

    return arr;
}

__attribute__((const))
#ifdef DEBUG
inline num_arr2D error2D(const num_arr2D& a, const num_arr2D& b, std::size_t n)
#else
inline num_arr2D error2D(const num_arr2D& a, const num_arr2D& b, std::size_t n) noexcept
#endif
{
#ifdef DEBUG
    assert(a.size() == b.size());
    assert(a.size() == n);
#endif

    num_arr2D arr = num_arr2D(n, num_arr(0, zero));
    for (std::size_t i = 0; i < n; ++i)
    {
        arr[i].resize(a[i].size());
        for (std::size_t j = 0; j < a[i].size(); ++j)
            arr[i][j] += a[i][j] - b[i][j];
    }

    return arr;
}
