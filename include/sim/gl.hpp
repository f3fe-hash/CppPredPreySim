#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "sim/defs.hpp"

class GLContext
{
    int window;
public:
    GLContext(int argc, char** argv);
    ~GLContext() = default;
};
