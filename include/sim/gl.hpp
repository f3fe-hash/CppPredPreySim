#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "sim/defs.hpp"

struct Object
{
    dim2 centerPos;
    RayHitType type;

    int id;
};

// Center point & type of object
inline vec<Object> objects;

class GLContext
{
    int window;

    static GLContext* __inst;

    void display();
    void reshape(int x, int y);

    void init();

    // Wrapper function for display
    static inline void _display_wrapper()
    {__inst->display();}

    // Wrapper function for reshape
    static inline void _reshape_wrapper(int x, int y)
    {__inst->reshape(x, y);}

public:
    GLContext(int argc, char** argv);
    ~GLContext() = default;

    void start()
    {
        glutMainLoop();
    }
};

void update() noexcept;
