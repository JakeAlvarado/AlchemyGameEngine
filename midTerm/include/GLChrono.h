#ifndef GLCHRONO_H
#define GLCHRONO_H

#include <common.h>

class GLChrono
{

    time_point<steady_clock> time;

    public:
    void set_timer(); // sets clock to current time
    int get_delta_time(); // return the amount of time passed



};

#endif // GLCHRONO_H
