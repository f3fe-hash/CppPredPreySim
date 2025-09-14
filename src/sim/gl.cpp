#include "sim/gl.hpp"

GLContext* GLContext::__inst = nullptr;

// Initialize OpenGL
GLContext::GLContext(int argc, char** argv)
{
    this->__inst = this;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SIM_WINDOW_SIZE.x, SIM_WINDOW_SIZE.y);
    this->window = glutCreateWindow("AI Pred vs. Prey Simulation");

    this->init();

    glutDisplayFunc(this->_display_wrapper);
    glutReshapeFunc(this->_reshape_wrapper);
}

void GLContext::init()
{}

// Drawing code goes here
void GLContext::display()
{
    // update() is an update for other non-graphics tasks (ex. AIs, changing object positions)
    // update() should be called first, over graphics functions, because otherwise, the simulation
    // will be 1 frame ahead of what is shown 
    update();

    // Swap buffs
    glutSwapBuffers();
}

void GLContext::reshape(int x, int y)
{
    (void) x;
    (void) y;
}