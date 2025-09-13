#include "sim/gl.hpp"

GLContext* GLContext::__inst = nullptr;

// Initialize OpenGL
GLContext::GLContext(int argc, char** argv)
{
    this->__inst = this;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SIM_WINDOW_SIZE.x, SIM_WINDOW_SIZE.y);
    this->window = glutCreateWindow("AI Pred vs. Prey SImulation");

    this->init();

    glutDisplayFunc(this->_display_wrapper);
    glutReshapeFunc(this->_reshape_wrapper);
}

void GLContext::init()
{}

// Drawing code goes here
void GLContext::display()
{
    // update() is an update for AIs, and other non-graphics tasks (ex. changing object positions)
    update();
    glutSwapBuffers();
}

void GLContext::reshape(int x, int y)
{
    (void) x;
    (void) y;
}