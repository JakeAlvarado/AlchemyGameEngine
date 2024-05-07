#include "GLChrono.h"


void GLChrono::set_timer()
{
    time = steady_clock::now();
}

int GLChrono::get_delta_time()
{


    steady_clock::time_point currentTime = steady_clock::now();

    duration<double, std::milli> deltaTime = currentTime - time;

    return deltaTime.count();

}
