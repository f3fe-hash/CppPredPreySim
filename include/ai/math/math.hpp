#pragma once

#include "ai/utils/defs.hpp"

#if defined(USE_CUDA)
    #include "ai/math/math_cuda.cu"
#elif defined(USE_OPENCL)
    #error "OpenCL is not yet supported."
    //#include "ai/math/math_opencl.hpp"
#else
    #include "ai/math/math_cpu.hpp"
#endif
