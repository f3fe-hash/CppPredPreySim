#pragma once

#if defined(USE_CUDA)
    #include "math/math_cuda.cu"
#elif defined(USE_OPENCL)
    #error "OpenCL is not yet supported."
    //#include "ai/math/math_opencl.hpp"
#else
    #include "math/math_cpu.hpp"
#endif
