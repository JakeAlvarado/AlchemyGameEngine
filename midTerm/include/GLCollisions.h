#ifndef GLCOLLISIONS_H
#define GLCOLLISIONS_H

#include <GLCheckCollision.h>
#include <common.h>

class GLCollisions
{
    public:
        GLCollisions();
        GLCollisions(vec2, float, float);           // this might be useful later if make a level class
        vec2 pos;
        float length;
        float width;
        virtual ~GLCollisions();
    private:
};

#endif