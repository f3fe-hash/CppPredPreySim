PredNN
--------------

The predator's neural network is structured with 20 inputs (one input for each
line of sight), then a hidden layer of size 10, then output of size 2 (how much the
predator wants to move in the x, y directions). Each line of sight vaue is a ray, cast
from the predator's body, at 3 degrees apart from each other, making the predator have
a 60 degree vision range. However, it gets to look 200px far, because of it's low
vision angle.

PreyNN
--------------

The prey's neural network is the same as the predator's neural network. But here, the
rays are cast 10 degrees apart from each other, making the prey have a 200 degree vision
range. But, it only gets to look 75px far.

OpenGL
------

Most of the OpenGL code is in src/main.cpp, src/sim/gl.cpp, and include/sim/gl.hpp. The
GLContext class contains the OpenGL context for drawing shapes, updating the screen,
and other OpenGL / graphics related routines.